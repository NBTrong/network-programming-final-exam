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
 * @brief Router for handling room-related messages.
 *
 * This function routes incoming room-related messages to appropriate handlers based on the message content.
 *
 * @param client_socket The socket of the client sending the message.
 * @param message The room-related message received from the client.
 */
Room *find_room_by_socket_id(int socket_id);

/**
 * @brief Add a room to the room list.
 * 
 * This function adds a room to the list of game rooms.
 * 
 * @param sender_socket_id The socket ID of the sender.
 * @param receiver_socket_id The socket ID of the receiver.
 * @param sender_username The username of the sender.
 * @param receiver_username The username of the receiver.
 * @return The room added.
*/
Room *add_room(
    int sender_socket_id,
    int receiver_socket_id,
    char *sender_username,
    char *receiver_username);

/**
 * @brief Remove a room from the room list.
 * 
 * This function removes a room from the list of game rooms.
 * 
 * @param sender_socket_id The socket ID of the sender.
 * @param receiver_socket_id The socket ID of the receiver.
 * @param sender_username The username of the sender.
 * @param receiver_username The username of the receiver.
 * @return The room removed.
 */
void remove_room(
    int sender_socket_id,
    int receiver_socket_id,
    char *sender_username,
    char *receiver_username);

void send_to_queue(Room *room);

#endif