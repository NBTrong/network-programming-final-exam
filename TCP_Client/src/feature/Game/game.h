#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/select.h>
#include <unistd.h>

#include "../../global.h"
#include "../../config/tcp.h"
#include "../../utils/utils.h"
#include "../../global.h"
#include "../../utils/utils.h"
#include "../Receiver/receiver.h"

/**
 * @brief Convert a string to an integer.
 *
 * This function attempts to convert a given string to an integer and returns the result.
 *
 * @param str The string to be converted.
 * @return The converted integer, or -1 if conversion is unsuccessful, or -2 if the string is not a valid integer.
 */
int convert_string_to_number(const char *str);

/**
 * @brief Draw the Tic-Tac-Toe game board.
 *
 * This function prints the current state of the Tic-Tac-Toe game board to the console.
 *
 * @param board A 3x3 array representing the game board.
 */
void draw_board(char board[][3]);

/**
 * @brief Allow the player to take a turn in the game.
 *
 * This function prompts the player to make a move by entering a number from 1 to 9 or 10 to accept defeat and cancel the game.
 *
 * @param sockfd The socket used for communication with the server.
 */
void take_turn(int sockfd);


/**
 * @brief Receive and update the game board based on the server's message.
 *
 * This function receives a message from the server containing the player's move and updates the game board accordingly.
 *
 * @param sockfd The socket used for communication with the server.
 * @param board A 3x3 array representing the game board.
 */
void get_update(int sockfd, char board[][3]);

/**
 * @brief Start and play the Tic-Tac-Toe game.
 *
 * This function handles the entire Tic-Tac-Toe game, including game setup, player turns, and game outcome.
 *
 * @param sockfd The socket used for communication with the server.
 */
void game(int server_socket);

#endif
