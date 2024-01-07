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

typedef struct Room
{
  int sender_socket_id;
  int receiver_socket_id;
  struct Room *next;
} Room;

extern Room *room_list;

Room *find_room_by_socket_id(int socket_id);

#endif