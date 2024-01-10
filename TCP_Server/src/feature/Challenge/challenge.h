#ifndef CHALLENGE_H
#define CHALLENGE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "../../global.h"
#include "../Session/session.h"
#include "../../utils/utils.h"
#include "../../config/tcp.h"
#include "../Room/room.h"
#include "../Rank/rank.h"

typedef struct Challenge
{
  int sender_socket_id;
  int receiver_socket_id;
  char sender_username[STRING_LENGTH];
  char receiver_username[STRING_LENGTH];
  struct Challenge *next;
} Challenge;

extern Challenge *challenge_list;

/**
 * @brief Router for handling challenge-related messages.
 *
 * This function routes incoming challenge-related messages to appropriate handlers based on the message content.
 *
 * @param client_socket The socket of the client sending the message.
 * @param message The challenge-related message received from the client.
 */
void challenge_router(int client_socket, const char *message);

/**
 * @brief Send a challenge to another user.
 *
 * This function allows a user to send a challenge to another user.
 *
 * @param client_socket The socket of the client sending the challenge.
 * @param parameter The challenge message containing recipient's username.
 */
void send_challenge(int client_socket, const char *parameter);

/**
 * @brief Add a challenge to the challenge list.
 *
 * This function adds a challenge to the list of pending challenges.
 *
 * @param sender_socket_id The socket ID of the sender.
 * @param receiver_socket_id The socket ID of the receiver.
 * @param sender_username The username of the sender.
 * @param receiver_username The username of the receiver.
 */
void add_challenge(
    int sender_socket_id,
    int receiver_socket_id,
    char *sender_username,
    char *receiver_username);

/**
 * @brief Handle cancellation of a challenge.
 *
 * This function handles the cancellation of a challenge by the sender.
 *
 * @param client_socket The socket of the client sending the cancellation request.
 * @param enemy_username The username of the challenged opponent.
 */
void handle_cancel_challenge(int client_socket, char *enemy_username);

/**
 * @brief Find a challenge by sender and receiver socket IDs.
 *
 * This function finds a challenge based on the sender and receiver socket IDs.
 *
 * @param sender_socket_id The socket ID of the sender.
 * @param receiver_socket_id The socket ID of the receiver.
 * @return A pointer to the Challenge structure if found; otherwise, NULL.
 */
Challenge *find_challenge(int sender_socket_id, int receiver_socket_id);

/**
 * @brief Get a list of pending challenges for a user.
 *
 * This function retrieves and sends a list of pending challenges to a user.
 *
 * @param client_socket The socket of the client requesting the list.
 */
void get_challenged_list(int client_socket);

/**
 * @brief Handle rejection of a challenge.
 *
 * This function handles the rejection of a challenge by the receiver.
 *
 * @param client_socket The socket of the client rejecting the challenge.
 * @param sender_username The username of the challenger.
 */
void handle_reject_challenge(int client_socket, char *sender_username);

/**
 * @brief Handle acceptance of a challenge.
 *
 * This function handles the acceptance of a challenge by the receiver.
 *
 * @param client_socket The socket of the client accepting the challenge.
 * @param sender_username The username of the challenger.
 */
void handle_accept_challenge(int client_socket, char *sender_username);

/**
 * @brief Delete challenges associated with a receiver socket ID.
 *
 * This function deletes challenges based on the receiver socket ID.
 *
 * @param socket_id The socket ID of the receiver.
 */
void delete_challenges_by_receiver_socket_id(int socket_id);

/**
 * @brief Delete challenges associated with a sender socket ID.
 *
 * This function deletes challenges based on the sender socket ID.
 *
 * @param socket_id The socket ID of the sender.
 */
void delete_challenges_by_sender_socket_id(int socket_id);


/**
 * @brief Update user scores after a challenge.
 *
 * This function updates user scores after a challenge, including the winner and loser.
 *
 * @param winner_username The username of the challenge winner.
 * @param loser_username The username of the challenge loser.
 */
void update_scores(const char *winner_username, const char *loser_username);

/**
 * @brief Print the list of challenges (for debugging purposes).
 */
void print_challenge_list();

/**
 * @brief Print the list of rooms (for debugging purposes).
 */
void printf_room_list();

#endif