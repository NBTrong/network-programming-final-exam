#include "auth.h"

void signUp(int socket)
{
  char username[STRING_LENGTH];
  char buffer[STRING_LENGTH];
  char message[STRING_LENGTH + 8];

  printf("Enter username: ");
  input(username, "string");

  sprintf(message, "SIGNUP %s", username);

  send_with_error_handling(
      socket,
      buffer,
      message,
      "Send message login status error");

  // recv_with_error_handling(
  //     socket,
  //     buffer,
  //     sizeof(buffer),
  //     "Error receiving data from the client");
  // printStatusMessage(buffer);
}

void login(int socket)
{
  char username[STRING_LENGTH];
  char buffer[STRING_LENGTH];
  char message[STRING_LENGTH + 5];

  printf("Enter username: ");
  input(username, "string");

  sprintf(message, "USER %s", username);

  send_with_error_handling(
      socket,
      buffer,
      message,
      "Send message login status error");

  // recv_with_error_handling(
  //     socket,
  //     buffer,
  //     sizeof(buffer),
  //     "Error receiving data from the client");
  // printStatusMessage(buffer);
}

void logout(int socket)
{
  char buffer[STRING_LENGTH];

  send_with_error_handling(
      socket,
      buffer,
      "BYE",
      "Send message login status error");

  // recv_with_error_handling(
  //     socket,
  //     buffer,
  //     sizeof(buffer),
  //     "Error receiving data from the client");
  // printStatusMessage(buffer);
}