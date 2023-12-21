
// void printEachUserRank(char *username, int score, char *status){
//     printf("|%8d|%10s|%15d|%6s|\n",1234,username, score, status);
// }
void printEachUserRank()
{

    printf("|%8d|%10s|%15d|%6s|\n", 1234, "chien", 650, "online");
    printf("|%8d|%10s|%15d|%6s|\n", 1234, "chien", 650, "online");
    printf("|%8d|%10s|%15d|%6s|\n", 1234, "chien", 650, "online");
    printf("|%8d|%10s|%15d|%6s|\n", 1234, "chien", 650, "online");
    printf("|%8d|%10s|%15d|%6s|\n", 1234, "chien", 650, "online");
    printf("|%8d|%10s|%15d|%6s|\n", 1234, "chien", 650, "online");
    printf("|%8d|%10s|%15d|%6s|\n", 1234, "chien", 650, "online");
}

void printUserRank()
{
    printf("|%8s|%10s|%15s|%6s|\n", "UserID", "  Username", "Ranking Score", "Status");
    printf("|%8s|%10s|%15s|%6s|\n", "--------", "----------", "--------------", "------");
    printEachUserRank();
}
void rankingScreen()
{
    char ch1;
    printUserRank();
    printf("Enter to back to menu\n");

    // system("pause");
    getchar();
    // system("clear");
}