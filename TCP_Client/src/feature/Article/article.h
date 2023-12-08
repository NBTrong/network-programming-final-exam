#ifndef ARTICLE_H
#define ARTICLE_H

#include "../../config/tcp.h"
#include "../../global.h"
#include "../../utils/utils.h"

/**
 * @brief Post an article to the server.
 *
 * This function prompts the user to enter an article, sends a post message to the server,
 * receives the post status from the server, and prints the status message.
 *
 * @param socket The socket used for communication with the server.
 */
void postArticle(int socket);

#endif // ARTICLE_H
