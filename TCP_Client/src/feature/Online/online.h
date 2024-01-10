#ifndef ONLINE_H
#define ONLINE_H

#include "../../config/tcp.h"
#include "../../global.h"
#include "../../utils/utils.h"

/**
 * @brief Process and display the list of online users.
 *
 * This function takes a string containing a list of online users and their status and displays it in a readable format.
 *
 * @param userList The string containing the list of online users and their statuses.
 */
void get_list_user_online(int socket);

/**
 * @brief Request and display the list of online users from the server.
 *
 * This function sends a request to the server to retrieve the list of online users and then processes and displays the list.
 *
 * @param socket The socket used for communication with the server.
 */
void process_user_list(const char *userList);

#endif
