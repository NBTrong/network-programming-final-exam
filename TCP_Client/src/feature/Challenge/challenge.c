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

      // Process data received from the server
      printf("Received from server: %s\n", buffer);
    }

    if (FD_ISSET(STDIN_FILENO, &read_fds))
    {
      // Read user input from stdin
      int choice;
      input(&choice, "int");

      // Remove challenge
      sprintf(message, "CHALLENGE DELETE %s", enemy_username);
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
  char buffer[STRING_LENGTH];
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
  printf("Recv from server: %s\n", buffer);
};