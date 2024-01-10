#ifndef ROOM_H
#define ROOM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "../../global.h"
#include "../Session/session.h"
#include "../../utils/utils.h"
#include "../../config/tcp.h"
#include <sys/ipc.h>
#include <sys/msg.h>

typedef struct Room
{
  int sender_socket_id;
  int receiver_socket_id;
  char sender_username[STRING_LENGTH];
  char receiver_username[STRING_LENGTH];
  struct Room *next;
} Room;

typedef struct Message
{
  long mess_type;
  Room room_data;
} Message;

extern Room *room_list;

/**
 * @brief Find a room by socket ID.
 *
 * This function searches for a room in the room list based on the socket ID of either the sender or the receiver.
 *
 * @param socket_id The socket ID of the sender or receiver to match.
 * @return A pointer to the Room if found, or NULL if not found.
 */
Room *find_room_by_socket_id(int socket_id);

/**
 * @brief Add a new room to the room list.
 *
 * This function adds a new room to the room list with the specified sender and receiver socket IDs, as well as their usernames.
 *
 * @param sender_socket_id The socket ID of the sender.
 * @param receiver_socket_id The socket ID of the receiver.
 * @param sender_username The username of the sender.
 * @param receiver_username The username of the receiver.
 * @return A pointer to the newly created Room.
 */
Room *add_room(
    int sender_socket_id,
    int receiver_socket_id,
    char *sender_username,
    char *receiver_username);

/**
 * @brief Remove a room from the room list.
 *
 * This function removes a room from the room list based on the specified sender and receiver socket IDs and usernames.
 *
 * @param sender_socket_id The socket ID of the sender.
 * @param receiver_socket_id The socket ID of the receiver.
 * @param sender_username The username of the sender.
 * @param receiver_username The username of the receiver.
 */
void remove_room(
    int sender_socket_id,
    int receiver_socket_id,
    char *sender_username,
    char *receiver_username);

/**
 * @brief Send a room to the message queue.
 *
 * This function sends a room to the message queue for further processing in a separate thread.
 *
 * @param room A pointer to the Room to be sent to the queue.
 */
void send_to_queue(Room *room);

#endif