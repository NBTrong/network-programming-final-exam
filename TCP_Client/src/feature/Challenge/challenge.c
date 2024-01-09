#include "challenge.h"
#include <unistd.h>

void challenge(int socket)
{
  char enemy_username[STRING_LENGTH];
  char buffer[STRING_LENGTH];
  char message[STRING_LENGTH + STRING_LENGTH];

  printf("Enter enemy username: ");
  input(enemy_username, "string");

  sprintf(message, "CHALLENGE SEND %s", enemy_username);

  send_with_error_handling(
      socket,
      buffer,
      message,
      "Send message login status error");

  recv_with_error_handling(
      socket,
      buffer,
      sizeof(buffer),
      "Error receiving data from the client");
  if (handle_response(buffer) == NULL)
  {
    return;
  }

  printf("Recv from server: %s \n", buffer);

  printf("Waiting enemy ...\n");
  printf("If you want to exit, enter any characters\n");
  fd_set read_fds;
  FD_ZERO(&read_fds);
  FD_SET(socket, &read_fds);
  FD_SET(STDIN_FILENO, &read_fds);
  int ready = select(socket + 1, &read_fds, NULL, NULL, NULL);
  if (ready > 0)
  {
    if (FD_ISSET(socket, &read_fds))
    {
      char buffer[1024];
      recv_with_error_handling(
          socket,
          buffer,
          sizeof(buffer),
          "Error receiving data from the client");

      if (strncmp(buffer, "SUCCESS", 7) != 0)
      {
        return;
      }
      else
      {
        game(socket);
      }
    }

    if (FD_ISSET(STDIN_FILENO, &read_fds))
    {
      // Read user input from stdin
      int choice;
      input(&choice, "int");

      // Remove challenge
      sprintf(message, "CHALLENGE CANCEL %s", enemy_username);
      send_with_error_handling(
          socket,
          buffer,
          message,
          "Send message login status error");
      recv_with_error_handling(
          socket,
          buffer,
          sizeof(buffer),
          "Error receiving data from the client");
      printf("Recv from server: %s\n", buffer);
    }
  }

  FD_ZERO(&read_fds);
  FD_SET(socket, &read_fds);
  FD_SET(STDIN_FILENO, &read_fds);
}

void get_challenged_list(int client_socket)
{
  int choice = 0;
  char buffer[STRING_LENGTH];
  char enemy[STRING_LENGTH];
  char message[STRING_LENGTH * 2];
  do
  {
    send_with_error_handling(
        client_socket,
        buffer,
        "CHALLENGE LIST",
        "Send message login status error");
    recv_with_error_handling(
        client_socket,
        buffer,
        sizeof(buffer),
        "Error receiving data from the client");
    char *data = handle_response(buffer);
    if (data != NULL)
    {
      // Create a copy of the input string that can be modified
      char userListCopy[STRING_LENGTH];
      strncpy(userListCopy, data, sizeof(userListCopy));

      char *token = strtok(userListCopy, " "); // Split the first username
      int userCount = 0;

      while (token != NULL)
      {
        printf("%s challenging\n", token);
        token = strtok(NULL, " ");
        userCount++;
      }

      // Check if no users are online and replace with a space if needed
      if (userCount == 0)
      {
        printf("No users challenging\n");
      }
    }
    else
    {
      return;
    }

    printf("Menu:\n");
    printf("1. Challenge Accept\n");
    printf("2. Challenge Reject\n");
    printf("3. Quit\n");
    printf("Enter your choice (1, 2, or 3): ");
    input(&choice, "int");

    switch (choice)
    {
    case 1:
      // Challenge Accept
      printf("Enter the username of the opponent you want to challenge: ");
      input(enemy, "string");
      snprintf(message, sizeof(message), "CHALLENGE ACCEPT %s", enemy);
      send_with_error_handling(
          client_socket,
          buffer,
          message,
          "Send message login status error");
      recv_with_error_handling(
          client_socket,
          buffer,
          sizeof(buffer),
          "Error receiving data from the client");
      if (handle_response(buffer) != NULL)
        game(client_socket);
      break;

    case 2:
      // Challenge Accept
      printf("Enter the username of the opponent you want to reject: ");
      input(enemy, "string");
      snprintf(message, sizeof(message), "CHALLENGE REJECT %s", enemy);
      send_with_error_handling(
          client_socket,
          buffer,
          message,
          "Send message login status error");
      recv_with_error_handling(
          client_socket,
          buffer,
          sizeof(buffer),
          "Error receiving data from the client");
      break;

    case 3:
      // Quit
      printf("Exiting the program.\n");
      return;

    default:
      // Invalid choice
      printf("Invalid choice. Please enter 1, 2, or 3.\n");
      break;
    }

  } while (choice != 3);
};