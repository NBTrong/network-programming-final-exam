#include "screens.h"

// void printEachUserRank(char *username, int score, char *status){
//     printf("|%8d|%10s|%15d|%8s|\n",1234,username, score, status);
// }
void printEachUserRank()
{

    printf("|%8d|%10s|%15d|%8s|\n", 1234, "chien", 650, "online");
    printf("|%8d|%10s|%15d|%8s|\n", 1234, "chien", 650, "online");
    printf("|%8d|%10s|%15d|%8s|\n", 1234, "chien", 650, "online");
    printf("|%8d|%10s|%15d|%8s|\n", 1234, "chien", 650, "online");
    printf("|%8d|%10s|%15d|%8s|\n", 1234, "chien", 650, "online");
    printf("|%8d|%10s|%15d|%8s|\n", 1234, "chien", 650, "online");
    printf("|%8d|%10s|%15d|%8s|\n", 1234, "chien", 650, "online");
}

void printUserRank()
{
    printf("|%8s|%10s|%15s|%8s|\n", "UserID ", " Username ", " Ranking Score ", " Status ");
    printf("|%8s|%10s|%15s|%8s|\n", "--------", "----------", "---------------", "--------");
    printEachUserRank();
}
void rankingScreen(int client_socket)
{
    printUserRank();
    printf("Enter to back to menu\n");

    getchar();
    // system("clear");
}