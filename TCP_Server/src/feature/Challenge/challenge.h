#ifndef CHALLENGE_H
#define CHALLENGE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "../../global.h"
#include "../Session/session.h"
#include "../../utils/utils.h"
#include "../../config/tcp.h"
#include "../Room/room.h"

typedef struct Challenge
{
  int sender_socket_id;
  int receiver_socket_id;
  char sender_username[STRING_LENGTH];
  char receiver_username[STRING_LENGTH];
  struct Challenge *next;
} Challenge;

extern Challenge *challenge_list;

void challenge_router(int client_socket, const char *message);

void send_challenge(int client_socket, const char *parameter);

void add_challenge(
    int sender_socket_id,
    int receiver_socket_id,
    char *sender_username,
    char *receiver_username);

void delete_challenge(int client_socket, const char *parameter);

Challenge *find_challenge(int sender_socket_id, int receiver_socket_id);

Challenge *find_challenge_by_receiver_socket_id(int receiver_socket_id);

void get_challenged_list(int client_socket);

#endif