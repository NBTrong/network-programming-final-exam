#ifndef TCP_H
#define TCP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/stat.h>
#include "../utils/utils.h"

/**
 * Send a message on the specified server socket with error handling.
 * @param server_socket The socket descriptor for the server connection.
 * @param buffer The buffer containing the message to send.
 * @param message The message to be sent on the server socket.
 * @param error_message The error message to display in case of sending failure.
 * @return 0 on success, or -1 in case of an error.
 */
int send_with_error_handling(const int server_socket, char *buffer, const char *message, const char *error_message);

/**
 * Receive a message on the specified client socket with error handling.
 * @param client_socket The socket descriptor for the client connection.
 * @param buffer The buffer to store the received message.
 * @param size The size of the buffer.
 * @param error_message The error message to display in case of receiving failure.
 * @return The number of bytes received on success, or -1 in case of an error.
 */
int recv_with_error_handling(const int client_socket, char *buffer, size_t size, const char *error_message);

/**
 * Initialize a server on the specified port number.
 * @param port_number The port number on which to initialize the server.
 * @return The socket descriptor for the server, or -1 in case of an error.
 */
int init_server(int port_number);

char *int_to_string(int num);

#endif