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
 * @brief Update player scores in the file.
 *
 * This function updates the scores of the winner and loser players in the player data file.
 *
 * @param winner_username The username of the winner.
 * @param loser_username The username of the loser.
 */
void update_scores(const char *winner_username, const char *loser_username);

/**
 * @brief Compare function for qsort to compare players by score.
 *
 * This function is used as a comparison function for qsort to sort players in descending order based on their scores.
 *
 * @param a Pointer to the first player.
 * @param b Pointer to the second player.
 * @return Positive if the second player has a higher score, negative if the first player has a higher score, and 0 if scores are equal.
 */
int compare_players(const void *a, const void *b);

/**
 * @brief Find the rank of a player by username.
 *
 * This function finds the rank (position) of a player in the leaderboard based on their username.
 *
 * @param players An array of Player structures representing the leaderboard.
 * @param num_players The number of players in the leaderboard.
 * @param username The username of the player to find.
 * @return The rank (position) of the player if found, or -1 if the player is not found.
 */
int find_player_rank(Player players[], int num_players, const char *username);

/**
 * @brief Read player data from a file and sort by score.
 *
 * This function reads player data from a file, sorts the players in descending order based on their scores, and returns the number of players read.
 *
 * @param players An array of Player structures to store player data.
 * @return The number of players read and sorted.
 */
int read_players_from_file(Player players[]);

/**
 * @brief Check the rank difference between two players.
 *
 * This function calculates and returns the rank difference between two players based on their usernames.
 *
 * @param username1 The username of the first player.
 * @param username2 The username of the second player.
 * @return The absolute rank difference between the two players.
 */
int check_rank_difference(const char *username1, const char *username2);

/**
 * @brief Find the score of a player by username.
 *
 * This function finds the score of a player in the leaderboard based on their username.
 *
 * @param players An array of Player structures representing the leaderboard.
 * @param num_players The number of players in the leaderboard.
 * @param username The username of the player to find.
 * @return The score of the player if found, or -9999 if the player is not found.
 */
int find_player_score(Player players[], int num_players, const char *username);

#endif