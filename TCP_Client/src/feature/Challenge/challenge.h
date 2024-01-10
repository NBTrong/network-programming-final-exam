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
 * @brief Challenge a user.
 * 
 * This function allows a user to challenge another user.
 * 
 * @param client_socket The socket of the client sending the message.
 * 
 * @return The challenge-related message received from the client.
*/
void challenge(int socket);
/**
 * 
 * @brief Get list of user challenged
 *  
 * This function allows a user to get list of user challenged
 * 
 * @param client_socket The socket of the client sending the message.
 * 
 * @return The challenge-related message received from the client.
*/
void get_challenged_list(int client_socket);

#endif // CHALLENGE_H
