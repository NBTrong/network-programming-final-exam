#ifndef RANK_H
#define RANK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../global.h"

typedef struct
{
  char username[50];
  int is_blocked;
  int score;
} Player;

/**
 * @brief Update scores of players after a game.
 *
 * This function updates the scores of players after a game based on the winner and loser.
 *
 * @param winner_username The username of the winner.
 * @param loser_username The username of the loser.
 */
void update_scores(const char *winner_username, const char *loser_username);

/**
 * @brief Compare function for sorting players by score in descending order.
 *
 * This function is used as a comparison function for qsort to sort players by score in descending order.
 *
 * @param a A pointer to the first player.
 * @param b A pointer to the second player.
 * @return Positive if the first player's score is greater, negative if the second player's score is greater, and zero if equal.
 */
int compare_players(const void *a, const void *b);

/**
 * @brief Find the rank of a player in the player array.
 *
 * This function finds the rank of a player in the player array based on their username.
 *
 * @param players The array of Player structures.
 * @param num_players The number of players in the array.
 * @param username The username of the player to find the rank for.
 * @return The rank of the player (1-indexed), or -1 if not found.
 */
int find_player_rank(Player players[], int num_players, const char *username);

/**
 * @brief Read players from file.
 *
 * This function reads players from the file and stores them in the player array.
 *
 * @param players The array of Player structures.
 * @return The number of players read.
 */
int read_players_from_file(Player players[]);

/**
 * @brief Check if rank difference is small than 10.
 * 
 * This function checks if the rank difference between two players is smaller than 10.
 * 
 * @param players The array of Player structures.
 * @param num_players The number of players in the array.
 */
int check_rank_difference(const char *username1, const char *username2);

/**
 * @brief Find the score of a player in the player array.
 *
 * This function finds the score of a player in the player array based on their username.
 *
 * @param players The array of Player structures.
 * @param num_players The number of players in the array.
 * @param username The username of the player to find the score for.
 * @return The score of the player, or -9999 if not found.
 */
int find_player_score(Player players[], int num_players, const char *username);

#endif