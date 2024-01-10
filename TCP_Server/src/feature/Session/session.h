#ifndef SESSION_H
#define SESSION_H

#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdio.h>
#include "../../global.h"
#include "../../config/tcp.h"
#include "../Auth/auth.h"
#include "../Room/room.h"

/**
 * @brief Represents a session with client information.
 *
 * This structure holds information about a client session, including the socket ID,
 * client IP address, communication port, associated username, login status, and a pointer
 * to the next session in the linked list.
 */
typedef struct Session
{
  int socket_id;                       // Socket ID associated with the session
  char client_addr[STRING_LENGTH];     // Client's IP address
  int port;                            // Port number for communication
  char client_username[STRING_LENGTH]; // Username associated with the session

  struct Session *next; // Pointer to the next session in the linked list
} Session;

extern Session *session_list; // External variable to store the linked list of sessions

/**
 * @brief Add a new session to the session list.
 *
 * This function creates a new session and adds it to the linked list of active sessions.
 *
 * @param socket_id The socket ID of the client.
 * @param client_addr The client's IP address.
 * @param port The client's port.
 * @param client_username The username of the client.
 */
void add_session(int socket_id, const char *client_addr, int port, const char *client_username);

/**
 * @brief Free the memory associated with the session list.
 *
 * This function releases the memory allocated for the linked list of sessions.
 */
void free_session_list();

/**
 * @brief Find a session by username.
 *
 * This function searches for a session with the given username in the session list.
 *
 * @param username The username to search for.
 * @return A pointer to the session if found, or NULL if not found.
 */
Session *find_session_by_username(const char *username);

/**
 * @brief Find a session by socket ID.
 *
 * This function searches for a session with the given socket ID in the session list.
 *
 * @param socket_id The socket ID to search for.
 * @return A pointer to the session if found, or NULL if not found.
 */
Session *find_session_by_socket_id(int socket_id);

/**
 * @brief Print information about all active sessions.
 *
 * This function prints information about all active sessions, including socket ID, client address, and username.
 */
void print_all_sessions();

/**
 * @brief Delete a session by its socket ID.
 *
 * This function removes a session with the given socket ID from the session list.
 *
 * @param socket_id The socket ID of the session to be deleted.
 */
void delete_session_by_socket_id(int socket_id);

/**
 * @brief Send a list of all active sessions to a client.
 *
 * This function sends a list of all logged-in users and their statuses to a client.
 *
 * @param client_socket The socket of the client to whom the list will be sent.
 */
void send_all_sessions(int client_socket);

#endif // SESSION_H
