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

Room *find_room_by_socket_id(int socket_id);

Room *add_room(
    int sender_socket_id,
    int receiver_socket_id,
    char *sender_username,
    char *receiver_username);

void remove_room(
    int sender_socket_id,
    int receiver_socket_id,
    char *sender_username,
    char *receiver_username);

void send_to_queue(Room *room);

#endif