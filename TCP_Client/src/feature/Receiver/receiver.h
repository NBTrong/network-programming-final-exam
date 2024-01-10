#ifndef RECEIVER_H
#define RECEIVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/stat.h>
#include "../../config/tcp.h"
#include "../../global.h"
#include "../../utils/utils.h"
#include <time.h>
#define FILE_SIZE_LIMIT 4294967296

/**
 * @brief Receive a file from a client using a predefined protocol.
 *
 * This function implements a protocol for receiving files from a client. It first receives the filename and size from the client, 
 * checks the file size limit, and then asks the client to send the file. It receives the file data and saves it to a file on the server.
 * 
 * @param sender_socket The socket of the client sending the file.
 */
void file_receiving_protocol(int sender_socket);

#endif