#ifndef CHALLENGE_H
#define CHALLENGE_H

#include <stdio.h>
#include "../../global.h"
#include "../../config/tcp.h"
#include "../../utils/utils.h"
#include "../../global.h"
#include <sys/select.h>
#include <unistd.h>
#include "../../utils/utils.h"
#include "../Game/game.h"

/**
 * @brief Send a challenge request to another user.
 * 
 * This function allows a user to send a challenge request to another user by specifying the opponent's username.
 * 
 * @param socket The socket of the client sending the challenge request.
 */
void challenge(int socket);

/**
 * @brief Get a list of users who have challenged you.
 *  
 * This function allows a user to retrieve a list of users who have challenged them.
 * 
 * @param client_socket The socket of the client requesting the list of challenges.
 */
void get_challenged_list(int client_socket);

#endif // CHALLENGE_H
