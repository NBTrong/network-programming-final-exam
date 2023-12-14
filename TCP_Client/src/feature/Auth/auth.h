#ifndef AUTH_H
#define AUTH_H

#include "../../global.h"
#include <stdio.h>
#include "../../config/tcp.h"
#include "../../utils/utils.h"

/**
 * @brief Prompt the user to enter a username and perform login.
 *
 * This function prompts the user to enter a username, sends a login message to the server,
 * receives the login status from the server, and prints the status message.
 *
 * @param socket The socket used for communication with the server.
 */
void login(int socket);

/**
 * @brief Perform logout operation.
 *
 * This function sends a logout message to the server, receives the logout status from the server,
 * and prints the status message.
 *
 * @param socket The socket used for communication with the server.
 */
void logout(int socket);

void signUp(int socket);

#endif // AUTH_H
