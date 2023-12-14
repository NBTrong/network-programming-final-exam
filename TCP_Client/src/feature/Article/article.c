#include "article.h"

void processUserList(const char *userList)
{
  // Create a copy of the input string that can be modified
  char userListCopy[STRING_LENGTH];
  strncpy(userListCopy, userList, sizeof(userListCopy));

  char *token = strtok(userListCopy, " "); // Split the first username
  while (token != NULL)
  {
    printf("%s online\n", token); // Print each username as "user online"
    token = strtok(NULL, " ");    // Split the next username
  }
}

void getListUserOnline(int socket)
{
  char buffer[STRING_LENGTH];
  char message[STRING_LENGTH + 5];

  sprintf(message, "ONLINE 1");

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
  processUserList(buffer);
}

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