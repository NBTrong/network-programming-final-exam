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
 * @brief Router function for handling challenge-related messages.
 *
 * This function routes incoming challenge-related messages to appropriate functions.
 *
 * @param client_socket The client socket.
 * @param message The incoming message.
 */
void challenge_router(int client_socket, const char *message);

/**
 * @brief Send a challenge to an enemy.
 *
 * This function sends a challenge to an enemy player.
 *
 * @param client_socket The client socket.
 * @param parameter The parameter containing the enemy's username.
 */
void send_challenge(int client_socket, const char *parameter);

/**
 * @brief Add a challenge to the challenge list.
 *
 * This function adds a challenge to the list of challenges.
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
 * @brief Handle the cancellation of a challenge.
 *
 * This function handles the cancellation of a challenge by a player.
 *
 * @param client_socket The client socket.
 * @param enemy_username The username of the player who sent the challenge.
 */
void handle_cancel_challenge(int client_socket, char *enemy_username);

/**
 * @brief Find a challenge in the challenge list.
 *
 * This function finds a challenge in the list of challenges based on sender and receiver socket IDs.
 *
 * @param sender_socket_id The socket ID of the sender.
 * @param receiver_socket_id The socket ID of the receiver.
 * @return A pointer to the found challenge or NULL if not found.
 */
Challenge *find_challenge(int sender_socket_id, int receiver_socket_id);

/**
 * @brief Get the list of challenges sent to a client.
 *
 * This function retrieves the list of challenges sent to a client and sends it as a response.
 *
 * @param client_socket The client socket.
 */
void get_challenged_list(int client_socket);

/**
 * @brief Handle the rejection of a challenge.
 *
 * This function handles the rejection of a challenge by a player.
 *
 * @param client_socket The client socket.
 * @param sender_username The username of the player who sent the challenge.
 */
void handle_reject_challenge(int client_socket, char *sender_username);

/**
 * @brief Handle the acceptance of a challenge.
 *
 * This function handles the acceptance of a challenge by a player.
 *
 * @param client_socket The client socket.
 * @param sender_username The username of the player who sent the challenge.
 */
void handle_accept_challenge(int client_socket, char *sender_username);

/**
 * @brief Delete challenges associated with a receiver socket ID.
 *
 * This function deletes challenges from the challenge list associated with a receiver socket ID.
 *
 * @param socket_id The socket ID of the receiver.
 */
void delete_challenges_by_receiver_socket_id(int socket_id);

/**
 * @brief Delete challenges associated with a sender socket ID.
 *
 * This function deletes challenges from the challenge list associated with a sender socket ID.
 *
 * @param socket_id The socket ID of the sender.
 */
void delete_challenges_by_sender_socket_id(int socket_id);


/**
 * @brief Update user scores after a challenge in feature/Rank/rank.h
 *
 * This function updates user scores after a challenge, including the winner and loser.
 *
 * @param winner_username The username of the challenge winner.
 * @param loser_username The username of the challenge loser.
 */
void update_scores(const char *winner_username, const char *loser_username);

/**
 * @brief Print the list of challenges.
 *
 * This function prints the list of challenges to the console.
 */
void print_challenge_list();

/**
 * @brief Print the list of rooms.
 *
 * This function prints the list of rooms to the console.
 */
void printf_room_list();

#endif