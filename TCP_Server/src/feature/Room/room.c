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

Room *add_room(
    int sender_socket_id,
    int receiver_socket_id,
    char *sender_username,
    char *receiver_username)
{
  pthread_mutex_lock(&mutex);
  Room *new_room = (Room *)malloc(sizeof(Room));
  new_room->sender_socket_id = sender_socket_id;
  new_room->receiver_socket_id = receiver_socket_id;
  strcpy(new_room->sender_username, sender_username);
  strcpy(new_room->receiver_username, receiver_username);
  new_room->next = room_list;
  room_list = new_room;
  pthread_mutex_unlock(&mutex);

  return new_room;
}

void remove_room(
    int sender_socket_id,
    int receiver_socket_id,
    char *sender_username,
    char *receiver_username)
{
  pthread_mutex_lock(&mutex);

  Room *current = room_list;
  Room *prev = NULL;

  // Traverse the list to find the room to remove
  while (current != NULL &&
         (current->sender_socket_id != sender_socket_id ||
          current->receiver_socket_id != receiver_socket_id ||
          strcmp(current->sender_username, sender_username) != 0 ||
          strcmp(current->receiver_username, receiver_username) != 0))
  {
    prev = current;
    current = current->next;
  }

  // If room is found, remove it
  if (current != NULL)
  {
    if (prev == NULL)
    {
      // If the room to be removed is the head
      room_list = current->next;
    }
    else
    {
      // If the room to be removed is not the head
      prev->next = current->next;
    }

    // Free memory allocated for the room
    free(current);
  }

  pthread_mutex_unlock(&mutex);
}

void send_to_queue(Room *room)
{
  struct Message msg;

  key_t key;
  int msgid;

  // ftok to generate unique key
  key = ftok("20194693", 65);

  // msgget creates a message queue
  // and returns identifier
  msgid = msgget(key, 0666 | IPC_CREAT);
  msg.mess_type = 1;

  memcpy(&msg.room_data, room, sizeof(Room));

  // Send the message to the queue
  if (msgsnd(msgid, &msg, sizeof(msg.room_data), 0) == -1)
  {
    perror("Error sending message to queue");
    exit(EXIT_FAILURE);
  }
}