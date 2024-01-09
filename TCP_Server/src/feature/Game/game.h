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

#define BOARD_SIZE 3
#define EMPTY 0
#define PLAYER1 1
#define PLAYER2 2

typedef struct
{
  int board[BOARD_SIZE][BOARD_SIZE];
  int current_player;
} Game;

void game(int player1_socket, int player2_socket);

#endif