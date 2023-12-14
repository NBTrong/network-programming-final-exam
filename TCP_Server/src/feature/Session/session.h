#ifndef SESSION_H
#define SESSION_H

#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdio.h>
#include "../../global.h"
#include "../../config/tcp.h"

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
  int login_status;                    // Login status (e.g., LOGGED_IN or NOT_LOGGED_IN)

  struct Session *next; // Pointer to the next session in the linked list
} Session;

extern Session *session_list; // External variable to store the linked list of sessions

/**
 * @brief Add a new session to the linked list.
 *
 * This function creates a new session with the provided information and adds it to the linked list.
 *
 * @param socket_id The socket ID associated with the session.
 * @param client_addr The client's IP address.
 * @param port The port number for communication.
 * @param client_username The username associated with the session.
 * @param login_status The login status (e.g., LOGGED_IN or NOT_LOGGED_IN).
 */
void add_session(int socket_id, const char *client_addr, int port, const char *client_username, int login_status);

/**
 * @brief Free the memory allocated for the session linked list.
 *
 * This function deallocates the memory used by the entire session linked list.
 */
void free_session_list();

/**
 * @brief Find a session by username.
 *
 * This function searches for a session with the specified username in the linked list.
 *
 * @param username The username to search for.
 * @return A pointer to the found session or NULL if not found.
 */
Session *find_session_by_username(const char *username);

/**
 * @brief Find a session by socket ID.
 *
 * This function searches for a session with the specified socket ID in the linked list.
 *
 * @param socket_id The socket ID to search for.
 * @return A pointer to the found session or NULL if not found.
 */
Session *find_session_by_socket_id(int socket_id);

/**
 * @brief Print information about all active sessions.
 *
 * This function prints information about all active sessions in the linked list.
 */
void print_all_sessions();

/**
 * @brief Delete a session by socket ID.
 *
 * This function removes the session with the specified socket ID from the linked list.
 *
 * @param socket_id The socket ID of the session to be deleted.
 */
void delete_session_by_socket_id(int socket_id);

void send_all_sessions(int client_socket);

#endif // SESSION_H
