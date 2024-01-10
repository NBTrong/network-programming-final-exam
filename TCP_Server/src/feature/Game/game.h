#ifndef GAME_H
#define GAME_H

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
#include "../Sender/sender.h"
#include "../Rank/rank.h"

#define BOARD_SIZE 3
#define EMPTY 0
#define PLAYER1 1
#define PLAYER2 2

typedef struct
{
  int board[BOARD_SIZE][BOARD_SIZE];
  int current_player;
} Game;

/**
 * @brief Start and manage a game between two players.
 *
 * This function initiates and manages a game between two players over the specified sockets.
 * It handles player moves, game outcomes, and logs the game details to a log file.
 *
 * @param player1_socket The socket of the first player.
 * @param player2_socket The socket of the second player.
 * @param player1_username The username of the first player.
 * @param player2_username The username of the second player.
 */
void game(int player1_socket, int player2_socket, char *player1_username, char *player2_username);

#endif