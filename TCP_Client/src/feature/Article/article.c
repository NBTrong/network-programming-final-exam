#include "article.h"

void postArticle(int socket)
{
  char article[STRING_LENGTH];
  char buffer[STRING_LENGTH];
  char message[STRING_LENGTH + 5];

  printf("Post article: ");
  input(article, "string");

  sprintf(message, "POST %s", article);

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
}