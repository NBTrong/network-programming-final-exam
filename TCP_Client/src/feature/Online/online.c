#include "online.h"

void process_user_list(const char *userList)
{
  // Create a copy of the input string that can be modified
  char userListCopy[STRING_LENGTH];
  strncpy(userListCopy, userList, sizeof(userListCopy));

  char *token = strtok(userListCopy, " "); // Split the first username
  int userCount = 0;

  while (token != NULL)
  {
    // Print the username
    printf("%s ", token);

    // Move to the next token (status)
    token = strtok(NULL, " ");

    // Print the status
    if (token != NULL)
    {
      printf("%s\n", token);
      userCount++;
    }
    else
    {
      // If there is no corresponding status, print an error message
      printf("Invalid format\n");
      break;
    }

    // Move to the next username
    token = strtok(NULL, " ");
  }

  // Check if no users are online and replace with a message if needed
  if (userCount == 0)
  {
    printf("No users online\n");
  }
}

void get_list_user_online(int socket)
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
  char *data = handle_response(buffer);
  if (data == NULL)
    return;
  process_user_list(data);
}