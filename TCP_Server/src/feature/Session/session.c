#include "session.h"

Session *session_list = NULL;

void add_session(int socket_id, const char *client_addr, int port, const char *client_username)
{
  pthread_mutex_lock(&session_mutex);
  Session *new_session = (Session *)malloc(sizeof(Session));
  new_session->socket_id = socket_id;
  strcpy(new_session->client_addr, client_addr);
  new_session->port = port;
  strcpy(new_session->client_username, client_username);

  new_session->next = session_list;
  session_list = new_session;
  pthread_mutex_unlock(&session_mutex);
}

void free_session_list()
{
  pthread_mutex_lock(&session_mutex);
  Session *current = session_list;
  Session *next;

  while (current != NULL)
  {
    next = current->next;
    free(current);
    current = next;
  }

  session_list = NULL;
  pthread_mutex_unlock(&session_mutex);
}

// Function to find a session by username
Session *find_session_by_username(const char *username)
{
  pthread_mutex_lock(&session_mutex);
  Session *current = session_list;

  while (current != NULL)
  {
    if (strcmp(current->client_username, username) == 0)
    {
      // Return a pointer to the session if the username matches
      pthread_mutex_unlock(&session_mutex);
      return current;
    }

    current = current->next;
  }

  // Return NULL if not found
  pthread_mutex_unlock(&session_mutex);
  return NULL;
}

Session *find_session_by_socket_id(int socket_id)
{
  pthread_mutex_lock(&session_mutex);
  Session *current = session_list;

  while (current != NULL)
  {
    if (current->socket_id == socket_id)
    {
      // Return a pointer to the session if the socket_id matches
      pthread_mutex_unlock(&session_mutex);
      return current;
    }

    current = current->next;
  }

  // Return NULL if not found
  pthread_mutex_unlock(&session_mutex);
  return NULL;
}

void print_all_sessions()
{
  // Lock the mutex before accessing shared data
  pthread_mutex_lock(&session_mutex);

  // Critical section: read shared data (e.g., session_list)
  Session *current = session_list;

  // Print header
  printf("Socket ID\tClient Address\t\t\tUsername\tLogin Status\n");

  // Print each session
  while (current != NULL)
  {
    printf("%d\t\t%s\t\t%s\n", current->socket_id,
           current->client_addr, current->client_username);
    current = current->next;
  }

  // Unlock the mutex after critical section
  pthread_mutex_unlock(&session_mutex);
}

void send_all_sessions(int client_socket)
{
  // Lock the mutex before accessing shared data
  pthread_mutex_lock(&session_mutex);

  // Critical section: read shared data (e.g., session_list)
  Session *current = session_list;
  char user_list[STRING_LENGTH] = "SUCCESS ";

  if (current == NULL)
  {
    send_with_error_handling(client_socket,
                             user_list,
                             user_list,
                             "Send user list error");
    return;
  }

  // Load player from file
  Player players[MAX_CLIENTS];
  int num_players = read_players_from_file(players);

  // Append usernames to the user_list string
  while (current != NULL)
  {
    int rank = find_player_rank(players, num_players, current->client_username);
    int score = find_player_score(players, num_players, current->client_username);
    char label[STRING_LENGTH];
    sprintf(label, "NO.%d(%d)---", rank, score);
    strcat(user_list, label);
    strcat(user_list, current->client_username);
    if (current->socket_id == client_socket)
    {
      strcat(user_list, ("(you)"));
    }
    strcat(user_list, " "); // Add a space to separate usernames

    // Find room

    if (find_room_by_socket_id(current->socket_id) == NULL)
    {
      strcat(user_list, "online ");
    }
    else
    {
      strcat(user_list, "playing ");
    }

    current = current->next;
    printf("User list: %s\n", user_list);
  }

  // Unlock the mutex after the critical section
  pthread_mutex_unlock(&session_mutex);

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
  pthread_mutex_lock(&session_mutex);

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
  pthread_mutex_unlock(&session_mutex);
}
