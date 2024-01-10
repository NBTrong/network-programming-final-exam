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
 * @brief Implement the file sending protocol.
 *
 * This function implements the protocol for sending a file to the server. It sends the file information, receives a request from the server to send the file, and then sends the file data.
 *
 * @param client_socket The socket to communicate with the server.
 * @param file_path The path to the file to be sent.
 */
void file_sending_protocol(int client_socket, char *file_path);

/**
 * @brief Handle a message received from the server.
 *
 * This function parses and handles a message received from the server, extracting the status and message parts.
 *
 * @param buffer The message received from the server.
 * @return The status part of the message.
 */
char *handle_message(const char *buffer);

#endif