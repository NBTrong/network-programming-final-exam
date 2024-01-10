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
 * @brief Send a message to both players in the game.
 *
 * This function sends a message to both players in the game using their respective sockets.
 *
 * @param player1_socket The socket of the first player.
 * @param player2_socket The socket of the second player.
 * @param message The message to send.
 */
void send_all(int player1_socket, int player2_socket, char *message);

/**
 * @brief Draw the Tic-Tac-Toe board.
 *
 * This function prints the current state of the Tic-Tac-Toe board.
 *
 * @param board A 2D array representing the Tic-Tac-Toe board.
 */
void draw_board(char board[][3]);

/**
 * @brief Convert a string to an integer.
 *
 * This function converts a string to an integer and returns the result.
 *
 * @param str The string to convert.
 * @return The integer value if conversion is successful, or -1 if the conversion fails.
 */
int convert_string_to_number(const char *str);

/**
 * @brief Get the move from a player.
 *
 * This function sends a "TURN" message to a player and receives their move.
 *
 * @param socket The socket of the player.
 * @return The player's move if received, or 0 if an error occurs.
 */
int get_player_move(int socket);

/**
 * @brief Check if a move is valid on the Tic-Tac-Toe board.
 *
 * This function checks if a move is valid on the board (not out of bounds and the position is not already occupied).
 *
 * @param board A 2D array representing the Tic-Tac-Toe board.
 * @param move The move to check.
 * @param player_id The ID of the player making the move (0 or 1).
 * @return 1 if the move is valid, 0 if it's invalid.
 */
int check_move(char board[][3], int move, int player_id);

/**
 * @brief Update the Tic-Tac-Toe board with a player's move.
 *
 * This function updates the Tic-Tac-Toe board with a player's move.
 *
 * @param board A 2D array representing the Tic-Tac-Toe board.
 * @param move The move to update.
 * @param player_id The ID of the player making the move (0 or 1).
 */
void update_board(char board[][3], int move, int player_id);

/**
 * @brief Send an update to both players.
 *
 * This function sends an update message to both players in the game, including the player's move and ID.
 *
 * @param cli_sockfd An array of player sockets.
 * @param move The move made by the player.
 * @param player_id The ID of the player making the move (0 or 1).
 */
void send_update(int *cli_sockfd, int move, int player_id);

/**
 * @brief Check if there is a winner on the Tic-Tac-Toe board.
 *
 * This function checks if there is a winner on the Tic-Tac-Toe board based on the last move made.
 *
 * @param board A 2D array representing the Tic-Tac-Toe board.
 * @param last_move The last move made.
 * @return 1 if there is a winner, 0 if not.
 */
int check_board(char board[][3], int last_move);

/**
 * @brief Start a Tic-Tac-Toe game between two players.
 *
 * This function handles a Tic-Tac-Toe game between two players using their respective sockets and usernames.
 *
 * @param player1_socket The socket of the first player.
 * @param player2_socket The socket of the second player.
 * @param player1_username The username of the first player.
 * @param player2_username The username of the second player.
 */
void game(int player1_socket, int player2_socket, char *player1_username, char *player2_username);

#endif