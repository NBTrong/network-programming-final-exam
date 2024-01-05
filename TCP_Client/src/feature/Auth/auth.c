#include "auth.h"

int login(int socket)
{
  char username[STRING_LENGTH];
  char buffer[STRING_LENGTH];
  char message[STRING_LENGTH + 5];
  int returnCode;
  printf("Enter username: ");
  // input(username, "string");
  scanf("%s", username);

  sprintf(message, "USER %s", username);
  // printf("\nsent message: '%s'\n", message);
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
  printStatusMessage(buffer);
  returnCode = atoi(buffer);
  return returnCode;
}

void logout(int socket)
{
  char buffer[STRING_LENGTH];

  send_with_error_handling(
      socket,
      buffer,
      "BYE",
      "Send message login status error");

  recv_with_error_handling(
      socket,
      buffer,
      sizeof(buffer),
      "Error receiving data from the client");
  printStatusMessage(buffer);
}