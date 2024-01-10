#include "game.h"

int convert_string_to_number(const char *str)
{
  // Check for NULL pointer
  if (str == NULL)
  {
    return -1; // Conversion unsuccessful
  }

  // Convert string to integer
  int result = atoi(str);

  // Check if the conversion was unsuccessful
  if (result == 0 && str[0] != '0')
  {
    return -2; // Conversion unsuccessful
  }

  return result; // Return the converted number
}

void draw_board(char board[][3])
{
  printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
  printf("-----------\n");
  printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
  printf("-----------\n");
  printf(" %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
}

void take_turn(int sockfd)
{
  char buffer[10];

  while (1)
  {
    printf("Enter 1-9 to make a move, or 10 to accept defeat and cancel the game: ");
    fgets(buffer, 10, stdin);
    int move = convert_string_to_number(buffer);
    if (move <= 10 && move >= 1)
    {
      printf("\n");
      send_with_error_handling(
          sockfd,
          buffer,
          int_to_string(move),
          "Send message failed");
      break;
    }
    else
      printf("\nInvalid input. Try again.\n");
  }
}

void get_update(int sockfd, char board[][3])
{
  char buffer[STRING_LENGTH];
  recv_with_error_handling(sockfd,
                           buffer,
                           sizeof(buffer),
                           "Error receiving data from the client");
  int player_id = convert_string_to_number(buffer);

  recv_with_error_handling(sockfd,
                           buffer,
                           sizeof(buffer),
                           "Error receiving data from the client");
  int move = convert_string_to_number(buffer);

  board[move / 3][move % 3] = player_id ? 'X' : 'O';
}

void game(int sockfd)
{
  char buffer[STRING_LENGTH];

  recv_with_error_handling(sockfd,
                           buffer,
                           sizeof(buffer),
                           "Error receiving data from the client");
  int id = convert_string_to_number(buffer);

  printf("[DEBUG] Client ID: %d\n", id);

  char board[3][3] = {{' ', ' ', ' '},
                      {' ', ' ', ' '},
                      {' ', ' ', ' '}};

  printf("Tic-Tac-Toe\n------------\n");

  do
  {
    recv_with_error_handling(sockfd,
                             buffer,
                             sizeof(buffer),
                             "Error receiving data from the client");
    if (!strcmp(buffer, "HLD"))
      printf("Waiting for a second player...\n");
  } while (strcmp(buffer, "START"));

  /* The game has begun. */
  printf("Game on!\n");

  draw_board(board);

  while (1)
  {
    recv_with_error_handling(sockfd,
                             buffer,
                             sizeof(buffer),
                             "Error receiving data from the client");

    if (!strcmp(buffer, "TURN"))
    {
      printf("Your move...\n");
      take_turn(sockfd);
    }
    else if (!strcmp(buffer, "INVALID"))
    {
      printf("That position has already been played. Try again.\n");
    }
    else if (!strcmp(buffer, "CNT"))
    {
      recv_with_error_handling(sockfd,
                               buffer,
                               sizeof(buffer),
                               "Error receiving data from the client");
      int num_players = convert_string_to_number(buffer);
      printf("There are currently %d active players.\n", num_players);
    }
    else if (!strcmp(buffer, "UPDATE"))
    {
      get_update(sockfd, board);
      draw_board(board);
    }
    else if (!strcmp(buffer, "WAIT"))
    {
      printf("Waiting for other players move...\n");
    }
    else if (!strcmp(buffer, "WIN"))
    {
      printf("You win!\n");
      break;
    }
    else if (!strcmp(buffer, "LOSE"))
    {
      printf("You lost.\n");
      break;
    }
    else if (!strcmp(buffer, "DRAW"))
    {
      printf("Draw.\n");
      break;
    }
    else
      printf("Unknown message.");
  }

  file_receiving_protocol(sockfd);

  printf("Game over.\n");
}