#include "rank.h"

int compare_players(const void *a, const void *b)
{
    return ((Player *)b)->score - ((Player *)a)->score;
}

int find_player_rank(Player players[], int num_players, const char *username)
{
    for (int i = 0; i < num_players; i++)
    {
        if (strcmp(players[i].username, username) == 0)
        {
            return i + 1; // Rank is 1-indexed
        }
    }
    return -1; // Player not found
}

int find_player_score(Player players[], int num_players, const char *username)
{
    for (int i = 0; i < num_players; i++)
    {
        if (strcmp(players[i].username, username) == 0)
        {
            return players[i].score; // Rank is 1-indexed
        }
    }
    return -9999; // Player not found
}

int read_players_from_file(Player players[])
{
    FILE *file = fopen("./TCP_Server/database/account.txt", "r");

    if (file == NULL)
    {
        printf("Unable to open the file.\n");
        exit(EXIT_FAILURE);
    }
    int num_players = 0;

    while (fscanf(file, "%s %d %d", players[num_players].username, &players[num_players].is_blocked, &players[num_players].score) == 3)
    {
        (num_players)++;
        if (num_players >= MAX_PLAYERS)
        {
            fprintf(stderr, "Too many players in the file. Increase MAX_PLAYERS.\n");
            fclose(file);
            exit(EXIT_FAILURE);
        }
    }

    fclose(file);

    // Sort players based on score
    qsort(players, num_players, sizeof(Player), compare_players);

    return num_players;
}

int check_rank_difference(const char *username1, const char *username2)
{
    // // Read file
    // FILE *file = fopen("./TCP_Server/database/account.txt", "r"); // Open the file in read mode ("r")

    // if (file == NULL)
    // {
    //     printf("Unable to open the file.\n");
    //     exit(1); // Exit the program with an error code
    // }

    // char line[MAX_LINE_LENGTH];
    // Player players[MAX_PLAYERS];
    // int num_players = 0;

    // // Read players from the file
    // while (fscanf(file, "%s %d %d", players[num_players].username, &players[num_players].is_blocked, &players[num_players].score) == 3)
    // {
    //     num_players++;
    //     if (num_players >= MAX_PLAYERS)
    //     {
    //         fprintf(stderr, "Too many players in the file. Increase MAX_PLAYERS.\n");
    //         fclose(file);
    //         exit(EXIT_FAILURE);
    //     }
    // }

    // // Sort players based on score
    // qsort(players, num_players, sizeof(Player), compare_players);

    Player players[MAX_PLAYERS];

    int num_players = read_players_from_file(players);

    // Find ranks of the two players
    int rank1 = find_player_rank(players, num_players, username1);
    int rank2 = find_player_rank(players, num_players, username2);

    printf("User1 rank: %d, user2 rank: %d\n", rank1, rank2);

    // Calculate rank difference and return the result
    int rank_difference = abs(rank1 - rank2);

    // Close the file before returning
    // fclose(file);

    return rank_difference;
}

void update_scores(const char *winner_username, const char *loser_username)
{
    FILE *file = fopen("./TCP_Server/database/account.txt", "r+");
    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }

    char line[MAX_LINE_LENGTH];
    Player players[MAX_PLAYERS];
    int num_players = 0;

    // Read players from the file
    while (fscanf(file, "%s %d %d", players[num_players].username, &players[num_players].is_blocked, &players[num_players].score) == 3)
    {
        num_players++;
        if (num_players >= MAX_PLAYERS)
        {
            fprintf(stderr, "Too many players in the file. Increase MAX_PLAYERS.\n");
            fclose(file);
            return;
        }
    }

    // Find the winner and loser in the player array
    int winner_index = -1, loser_index = -1;
    for (int i = 0; i < num_players; i++)
    {
        if (strcmp(players[i].username, winner_username) == 0)
        {
            winner_index = i;
        }
        else if (strcmp(players[i].username, loser_username) == 0)
        {
            loser_index = i;
        }
    }

    if (winner_index == -1 || loser_index == -1)
    {
        fprintf(stderr, "Winner or loser not found in the file.\n");
        fclose(file);
        return;
    }

    // Update scores
    players[winner_index].score += 3;
    players[loser_index].score -= 3;

    // Move the file pointer to the beginning of the file
    fseek(file, 0, SEEK_SET);

    // Write the updated scores back to the file
    for (int i = 0; i < num_players; i++)
    {
        fprintf(file, "%s %d %d\n", players[i].username, players[i].is_blocked, players[i].score);
    }

    // Close the file before returning
    fclose(file);
}
