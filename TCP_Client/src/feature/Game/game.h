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
 * @brief Start and manage a game between two players.
 * 
 * This function initiates and manages a game between two players over the specified sockets.
 * It handles player moves, game outcomes, and logs the game details to a log file.
 * 
 * @param server_socket The socket of the server.
 * 
 * @return The game-related message received from the client.
*/
void game(int server_socket);

#endif
