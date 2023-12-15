#include "session.h"

Session *session_list = NULL;

void add_session(int socket_id, const char *client_addr, int port, const char *client_username, int login_status)
{
  pthread_mutex_lock(&mutex);
  Session *new_session = (Session *)malloc(sizeof(Session));
  new_session->socket_id = socket_id;
  strcpy(new_session->client_addr, client_addr);
  new_session->port = port;
  strcpy(new_session->client_username, client_username);
  new_session->login_status = login_status;

  new_session->next = session_list;
  session_list = new_session;
  pthread_mutex_unlock(&mutex);
}

void free_session_list()
{
  pthread_mutex_lock(&mutex);
  Session *current = session_list;
  Session *next;

  while (current != NULL)
  {
    next = current->next;
    free(current);
    current = next;
  }

  session_list = NULL;
  pthread_mutex_unlock(&mutex);
}

// Function to find a session by username
Session *find_session_by_username(const char *username)
{
  pthread_mutex_lock(&mutex);
  Session *current = session_list;

  while (current != NULL)
  {
    if (strcmp(current->client_username, username) == 0)
    {
      // Return a pointer to the session if the username matches
      pthread_mutex_unlock(&mutex);
      return current;
    }

    current = current->next;
  }

  // Return NULL if not found
  pthread_mutex_unlock(&mutex);
  return NULL;
}

Session *find_session_by_socket_id(int socket_id)
{
  pthread_mutex_lock(&mutex);
  Session *current = session_list;

  while (current != NULL)
  {
    if (current->socket_id == socket_id)
    {
      // Return a pointer to the session if the socket_id matches
      pthread_mutex_unlock(&mutex);
      return current;
    }

    current = current->next;
  }

  // Return NULL if not found
  pthread_mutex_unlock(&mutex);
  return NULL;
}

void print_all_sessions()
{
  // Lock the mutex before accessing shared data
  pthread_mutex_lock(&mutex);

  // Critical section: read shared data (e.g., session_list)
  Session *current = session_list;

  // Print header
  printf("Socket ID\tClient Address\t\t\tUsername\tLogin Status\n");

  // Print each session
  while (current != NULL)
  {
    printf("%d\t\t%s\t\t%s\t\t%d\n", current->socket_id,
           current->client_addr, current->client_username, current->login_status);
    current = current->next;
  }

  // Unlock the mutex after critical section
  pthread_mutex_unlock(&mutex);
}

void send_all_sessions(int client_socket)
{
  // Lock the mutex before accessing shared data
  pthread_mutex_lock(&mutex);

  // Critical section: read shared data (e.g., session_list)
  Session *current = session_list;
  char user_list[STRING_LENGTH] = " "; // String to store the list of logged-in users

  if (current == NULL)
  {
    send_with_error_handling(client_socket,
                             user_list,
                             user_list,
                             "Send user list error");
    return;
  }
  // Append usernames to the user_list string
  while (current != NULL)
  {
    printf("username: %s\n", current->client_username);
    strcat(user_list, current->client_username);
    strcat(user_list, " "); // Add a space to separate usernames
    current = current->next;
    printf("User list: %s\n", user_list);
  }

  // Unlock the mutex after the critical section
  pthread_mutex_unlock(&mutex);

  // Send the list of logged-in users to the client
  char buffer[STRING_LENGTH];
  send_with_error_handling(client_socket,
                           buffer,
                           user_list,
                           "Send user list error");
}

void delete_session_by_socket_id(int socket_id)
{
  // Lock the mutex before accessing shared data
  pthread_mutex_lock(&mutex);

  // Critical section: update shared data (e.g., session_list)
  Session *current = session_list;
  Session *prev = NULL;

  // Find the session with the given socket_id
  while (current != NULL && current->socket_id != socket_id)
  {
    prev = current;
    current = current->next;
  }

  // If the session is found, remove it from the linked list
  if (current != NULL)
  {
    if (prev == NULL)
    {
      // The session is the first in the list
      session_list = current->next;
    }
    else
    {
      // The session is in the middle or at the end of the list
      prev->next = current->next;
    }

    // Free the memory for the deleted session
    free(current);
  }

  // Unlock the mutex after critical section
  pthread_mutex_unlock(&mutex);
}
