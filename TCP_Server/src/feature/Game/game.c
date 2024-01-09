#include "game.h"

void send_all(int player1_socket, int player2_socket, char *message)
{
    char buffer[STRING_LENGTH];
    send_with_error_handling(
        player1_socket,
        buffer,
        message,
        "Send message failed");
    send_with_error_handling(
        player2_socket,
        buffer,
        message,
        "Send message failed");
}

void draw_board(char board[][3])
{
    printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("-----------\n");
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("-----------\n");
    printf(" %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
}

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

int get_player_move(int socket)
{
    char buffer[STRING_LENGTH];
    send_with_error_handling(
        socket,
        buffer,
        "TRN",
        "Send message failed");

    recv_with_error_handling(socket,
                             buffer,
                             sizeof(buffer),
                             "Error receiving data from the client");
    return convert_string_to_number(buffer);
}

int check_move(char board[][3], int move, int player_id)
{
    if ((board[move / 3][move % 3] == ' '))
    {
        printf("[DEBUG] Player %d's move was valid.\n", player_id);
        return 1;
    }
    else
    {
        printf("[DEBUG] Player %d's move was invalid.\n", player_id);
        return 0;
    }
}

void update_board(char board[][3], int move, int player_id)
{
    board[move / 3][move % 3] = player_id ? 'X' : 'O';

    printf("[DEBUG] Board updated.\n");
}

void send_update(int *cli_sockfd, int move, int player_id)
{
    printf("[DEBUG] Sending update...\n");

    send_all(cli_sockfd[0], cli_sockfd[1], "UPD");

    send_all(cli_sockfd[0], cli_sockfd[1], int_to_string(player_id));

    send_all(cli_sockfd[0], cli_sockfd[1], int_to_string(move));

    printf("[DEBUG] Update sent.\n");
}

int check_board(char board[][3], int last_move)
{
    printf("[DEBUG] Checking for a winner...\n");

    int row = last_move / 3;
    int col = last_move % 3;

    if (board[row][0] == board[row][1] && board[row][1] == board[row][2])
    {
        printf("[DEBUG] Win by row %d.\n", row);
        return 1;
    }
    else if (board[0][col] == board[1][col] && board[1][col] == board[2][col])
    {
        printf("[DEBUG] Win by column %d.\n", col);
        return 1;
    }
    else if (!(last_move % 2))
    {
        if ((last_move == 0 || last_move == 4 || last_move == 8) && (board[1][1] == board[0][0] && board[1][1] == board[2][2]))
        {
            printf("[DEBUG] Win by backslash diagonal.\n");
            return 1;
        }
        if ((last_move == 2 || last_move == 4 || last_move == 6) && (board[1][1] == board[0][2] && board[1][1] == board[2][0]))
        {
            printf("[DEBUG] Win by frontslash diagonal.\n");
            return 1;
        }
    }

    printf("[DEBUG] No winner, yet.\n");

    return 0;
}

void game(int player1_socket, int player2_socket)
{
    char buffer[STRING_LENGTH];
    char board[3][3] = {{' ', ' ', ' '},
                        {' ', ' ', ' '},
                        {' ', ' ', ' '}};

    printf("Game on!\n");

    send_with_error_handling(
        player1_socket,
        buffer,
        int_to_string(player1_socket),
        "Send message failed");

    send_with_error_handling(
        player2_socket,
        buffer,
        int_to_string(player2_socket),
        "Send message failed");

    send_all(player1_socket, player2_socket, "SRT");

    draw_board(board);

    int players_socket[2] = {player1_socket, player2_socket};

    int prev_player_turn = 1;
    int player_turn = 0;
    int game_over = 0;
    int turn_count = 0;
    while (!game_over)
    {

        if (prev_player_turn != player_turn)
            send_with_error_handling(
                players_socket[(player_turn + 1) % 2],
                buffer,
                "WAT",
                "Send message failed");

        int valid = 0;
        int move = 0;
        while (!valid)
        {
            move = get_player_move(players_socket[player_turn]);
            if (move == -1)
                break;
            printf("Player %d played position %d\n", player_turn, move);

            valid = check_move(board, move, player_turn);

            if (!valid)
            {
                printf("Move was invalid. Let's try this again...\n");
                send_with_error_handling(
                    players_socket[player_turn],
                    buffer,
                    "INV",
                    "Send message failed");
            }
        }

        if (move == -1)
        {
            printf("Player disconnected.\n");
            break;
        }
        else
        {
            update_board(board, move, player_turn);
            send_update(players_socket, move, player_turn);

            draw_board(board);

            game_over = check_board(board, move);

            if (game_over == 1)
            {
                send_with_error_handling(
                    players_socket[player_turn],
                    buffer,
                    "WIN",
                    "Send message failed");
                send_with_error_handling(
                    players_socket[(player_turn + 1) % 2],
                    buffer,
                    "LSE",
                    "Send message failed");
                printf("Player %d won.\n", player_turn);
            }
            else if (turn_count == 8)
            {
                printf("Draw.\n");
                send_all(players_socket[player_turn], players_socket[(player_turn + 1) % 2], "DRW");
                game_over = 1;
            }

            prev_player_turn = player_turn;
            player_turn = (player_turn + 1) % 2;
            turn_count++;
        }
    }

    printf("Game over.\n");
}