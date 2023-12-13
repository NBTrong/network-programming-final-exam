#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define MAX_LEN 255
void loginScreen();
void lobbyScreen();
void readyScreen();
void inGameScreen();
void rankingScreen();
void challengeScreen();
// void Screen();


void loginScreen (){
    int menu;
    while (1)
    {
        printf (" =================== Caro =================== \n");
        printf (" 1. Login. \n");
        printf (" 2. Register. \n");
        printf (" 0. Exit program. \n");
        printf (" ============================================ \n");
        printf (" Enter your choice: ");
        scanf("%d",&menu);
        system("clear");
        switch (menu)
        {
        case 1:
            lobbyScreen();
            break;
        case 2:
            break;
        case 0:
            exit(0);
        default:
            break;
        }
    }
    
}
void registerScreen(){
    int menu;
    char username[MAX_LEN],password[MAX_LEN];
    while (1)
    {
        printf (" =================== Caro =================== \n");
        printf (" 1. Enter your username:"); scanf("%s",username);
        // printf (" 2. Enter your password:");
        printf (" Enter your choice: ");
        scanf("%d",&menu);
        system("clear");
        switch (menu)
        {
        case 1:
            lobbyScreen();
            break;
        case 2:
            break;
        case 0:
            exit(0);
        default:
            break;
        }
    }
}
void lobbyScreen(){
    int menu;
    system("clear");
    while (1)
    {
        printf (" =================== Caro =================== \n");
        printf (" Hello username ! Welcome back !\n");
        printf (" 1. Ready to game. \n");
        printf (" 2. Ranking. \n");
        printf (" 3. Chanllenge.\n");
        printf (" 4. Log out. \n");
        printf (" 0. Exit program. \n");
        printf (" ============================================ \n");
        printf (" Enter your choice: ");
        scanf("%d",&menu);
        system("clear");
        switch (menu)
        {
        case 1:
            readyScreen();
            break;
        case 2:
            rankingScreen();
            break;
        case 3:
            challengeScreen();
            break;
        case 4:
            loginScreen();
            break;
        case 0:
            exit(0);
        default:
            break;
        }
    }
    
}
void readyScreen()
{
    int menu;
    system("clear");
    while (1)
    {
        system("clear");
        printf (" =================== Caro =================== \n");
        printf (" username is ready, waiting for match ...\n");
        printf (" 1. Back to lobby \n");
        printf (" 0. Exit program. \n");
        printf (" ============================================ \n");
        printf (" Enter your choice: ");
        sleep(3);
        inGameScreen();
        scanf("%d",&menu);
        switch (menu)
        {
        case 1:
            lobbyScreen();
            break;
        case 0:
            exit(0);
        default:
            break;
        }
    }
}
void inGameScreen(){
    int menu,moveColumn,moveRow;
    int board[3][3]={0};
    system("clear");
    while (1)
    {
        printf (" \n=================== Caro =================== \n");
            printf ("|---|---|---|\n");

        for (int i = 0; i < 3; i++)
        {
            printf("| %s | %s | %s |\n",board[i][0]==0?" ":board[i][0]==1?"X":board[i][0]==2?"O",
                                        board[i][1]==0?" ":board[i][1]==1?"X":"O",
                                        board[i][2]==0?" ":board[i][2]==1?"X":"O");
            printf ("|---|---|---|\n");
        }
        printf ("1. Move \n");
        printf ("2. Quit game. \n");
        printf ("0. Exit program. \n");
        printf ("============================================ \n");
        printf ("Enter your choice: ");
        scanf("%d",&menu);
        switch (menu)
        {
        case 1:
            printf("Enter the position you want to move:\n");
            printf(" row   : ");scanf("%d",&moveColumn);
    
            printf(" column: ");scanf("%d",&moveRow);
            if (moveRow > 3 || moveColumn > 3)
            {
                printf("Wrong input. Please try again");
            }
            else
                board[moveColumn-1][moveRow-1]=1;
            break;
        case 2:
            system("clear");
            lobbyScreen();
        case 0:
            exit(0);
        default:
            break;
        }
        system("clear");
    }
}
// void printEachUserRank(char *username, int score, char *status){
//     printf("|%8d|%10s|%15d|%6s|\n",1234,username, score, status);
// }
void printEachUserRank(){

    printf("|%8d|%10s|%15d|%6s|\n",1234,"chien", 650, "online");
    printf("|%8d|%10s|%15d|%6s|\n",1234,"chien", 650, "online");
    printf("|%8d|%10s|%15d|%6s|\n",1234,"chien", 650, "online");
    printf("|%8d|%10s|%15d|%6s|\n",1234,"chien", 650, "online");
    printf("|%8d|%10s|%15d|%6s|\n",1234,"chien", 650, "online");
    printf("|%8d|%10s|%15d|%6s|\n",1234,"chien", 650, "online");
    printf("|%8d|%10s|%15d|%6s|\n",1234,"chien", 650, "online");
}

void printUserRank(){
    printf("|%8s|%10s|%15s|%6s|\n","UserID","  Username", "Ranking Score", "Status");
    printf("|%8s|%10s|%15s|%6s|\n","--------","----------", "--------------", "------");
    printEachUserRank();
}
void rankingScreen(){
    char ch1;
    printUserRank();
    printf("Enter to back to menu\n");
    
    // system("pause");
    getchar();
    // system("clear");
}
void challengeScreen(){
    rankingScreen();
    int chossenUser;
    printf("Enter the user ID you want to challenge: ");
    scanf("%d",&chossenUser);
    system("clear");
    printf("Challenge sent to user %d\n",chossenUser);
    printf("Waiting for response from user %d\n",chossenUser);
    // sleep(3);
    inGameScreen();
}
int main () {
    loginScreen();
}