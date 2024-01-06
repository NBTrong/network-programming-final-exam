#include "request.h"
#include <unistd.h>

void request(int socket)
{
  char opponent_username[STRING_LENGTH];
  char buffer[STRING_LENGTH];
  char message[STRING_LENGTH + 8];

  printf("Enter opponent username: ");
  input(opponent_username, "string");

  sprintf(message, "REQUEST %s", opponent_username);

  send_with_error_handling(
      socket,
      buffer,
      message,
      "Send message login status error");
}

void reply_request(int socket)
{
  char buffer[STRING_LENGTH];
  char message[STRING_LENGTH + 14];
  char result[STRING_LENGTH];
  write(STDOUT_FILENO, "\033[1;1H\033[2J", 10);
  printf("\nAccept? (yes/no): ");
  input(result, "string");

  sprintf(message, "REPLY_REQUEST %s", result);

  send_with_error_handling(
      socket,
      buffer,
      message,
      "Send message login status error");
}