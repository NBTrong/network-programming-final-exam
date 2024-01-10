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

void update_scores(const char *winner_username, const char *loser_username);

int compare_players(const void *a, const void *b);

int find_player_rank(Player players[], int num_players, const char *username);

int read_players_from_file(Player players[]);

int check_rank_difference(const char *username1, const char *username2);

int find_player_score(Player players[], int num_players, const char *username);

#endif