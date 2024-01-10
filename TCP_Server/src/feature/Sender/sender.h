#ifndef SENDER_H
#define SENDER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <libgen.h>
#include "../../config/tcp.h"

/**
 * Implement a file sending protocol on the specified client socket.
 * This function handles the process of sending a file from the client to the server.
 * @param client_socket The socket descriptor for the client connection.
 */
void file_sending_protocol(int client_socket, char *file_path);

/**
 * Handle a message from the client.
 * This function handles a message from the client and returns a response message.
 * @param buffer The message from the client.
 * @return The response message.
 */
char *handle_message(const char *buffer);

#endif