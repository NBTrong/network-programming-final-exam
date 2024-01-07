#ifndef TCP_H
#define TCP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <libgen.h>
#include "../feature/Article/article.h"
#include "../global.h"
#include "../feature/Challenge/challenge.h"

/**
 * Connect to a server using the specified IP address and port number.
 * @param server_ip_address The IP address of the server to connect to.
 * @param server_port_number The port number on the server to establish the connection.
 * @return A socket descriptor representing the connection to the server, or -1 in case of an error.
 */
int connect_server(const char *server_ip_address, int server_port_number);

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

void printStatusMessage(const char *status);

#endif