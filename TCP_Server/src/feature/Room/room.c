#include "room.h"

Room *room_list = NULL;

Room *find_room_by_socket_id(int socket_id)
{
  pthread_mutex_lock(&mutex);
  Room *current = room_list;

  while (current != NULL)
  {
    if (current->sender_socket_id == socket_id || current->receiver_socket_id == socket_id)
    {
      // Return a pointer to the Room if the socket_id matches
      pthread_mutex_unlock(&mutex);
      return current;
    }

    current = current->next;
  }

  // Return NULL if not found
  pthread_mutex_unlock(&mutex);
  return NULL;
}