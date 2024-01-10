#ifndef ONLINE_H
#define ONLINE_H

#include "../../config/tcp.h"
#include "../../global.h"
#include "../../utils/utils.h"

/**
 * @brief Get list user online
 * 
 * This function allows a user to get list user online
 * 
 * @param client_socket The socket of the client sending the message.
 * @return The online-related message received from the client.
*/
void get_list_user_online(int socket);

/**
 * @brief Process list user online
 * 
 * This function allows a user to process list user online
 * 
 * @param userList The list user online.
*/
void process_user_list(const char *userList);

#endif
