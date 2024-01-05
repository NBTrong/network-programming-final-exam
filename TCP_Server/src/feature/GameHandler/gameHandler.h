#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "../../global.h"
#include "../Session/session.h"
#include "../../utils/utils.h"
#include "../../config/tcp.h"

/**
 * @brief Represents a session with client information.
 *
 * This structure holds information about a client session, including the socket ID,
 * client IP address, communication port, associated username, login status, and a pointer
 * to the next session in the linked list.
 */
typedef struct Game
{
    int socket_id; // Socket ID associated with the session
    int port;      // Port number for communication
    int gameID;    // Game ID
    int client_send_challange_socket_turn_X;
    int client_receive_challange_socket_turn_O;
    int board[BOARD][BOARD];
    struct Game *next; // Pointer to the next session in the linked list
} Game;

extern Game *game_list;


int createNewGame(int client_send_challange_socket_turn_X,int client_receive_challange_socket_turn_O, int gameID);
/**
 */
int sendUserTurn(int client_socket, int userTurn);
/**
 */
int sendBoard(int client_socket, int board[BOARD][BOARD]);
/**
 */
int sendGameID(int client_socket, int gameID);
/**
 */
int sendChallange(int client_send_challange_socket, char *params);
/**
 */

int checkWinner(int board[BOARD][BOARD]);
/**
 */
int checkOver(int board[BOARD][BOARD]);
/**
*/
int sendAcceptChallange(int client_receive_challange_socket, char *params); 
/**
 */
// int sendDeclineChallange(int client_receive_challange_socket, char *params);
/**
 */
int updateMove(int client_send_challange_socket_turn_X,int client_receive_challange_socket_turn_O, char *params);
/**
 */
// int sendWin(int client_socket, char *params);
/**
 */
// int sendLose(int client_socket, char *params);
/**
 */
// int rejectChallange(int client_socket, char *params);


#endif