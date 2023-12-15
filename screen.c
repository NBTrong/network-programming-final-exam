#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define MAX_LEN 255
#define SQUARE 3
void loginScreen();
void lobbyScreen();
void readyScreen();
void inGameScreen();
void rankingScreen();
void challengeScreen();
// void Screen();

void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    { /* Clear input buffer */
    }
}
void loginScreen()
{
    int menu;
    while (1)
    {
        printf(" =================== Caro =================== \n");
        printf(" 1. Login. \n");
        printf(" 2. Register. \n");
        printf(" 0. Exit program. \n");
        printf(" ============================================ \n");
        printf(" Enter your choice: ");
        scanf("%d", &menu);
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
void registerScreen()
{
    int menu;
    char username[MAX_LEN], password[MAX_LEN];
    while (1)
    {
        printf(" =================== Caro =================== \n");
        printf(" 1. Enter your username:");
        scanf("%s", username);
        // printf (" 2. Enter your password:");
        printf(" Enter your choice: ");
        scanf("%d", &menu);
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
void lobbyScreen()
{
    int menu;
    system("clear");
    while (1)
    {
        printf(" =================== Caro =================== \n");
        printf(" Hello username ! Welcome back !\n");
        printf(" 1. Ready to game. \n");
        printf(" 2. Ranking. \n");
        printf(" 3. Chanllenge.\n");
        printf(" 4. Log out. \n");
        printf(" 0. Exit program. \n");
        printf(" ============================================ \n");
        printf(" Enter your choice: ");
        scanf("%d", &menu);
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
        printf(" =================== Caro =================== \n");
        printf(" username is ready, waiting for match ...\n");
        printf(" 1. Back to lobby \n");
        printf(" 0. Exit program. \n");
        printf(" ============================================ \n");
        // printf(" Enter your choice: ");
        // printf(" Join game in 3s\n");
        // sleep(1);
        // printf(" Join game in 2s\n");
        // sleep(1);
        // printf(" Join game in 1s\n");
        // sleep(1);
        inGameScreen();
        scanf("%d", &menu);
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
int checkWinner(int board[3][3])
{
    // printf("check winner\n");
    // clearInputBuffer(); // Clear the input buffer
    // getchar();
    // Check rows and columns for a win
    for (int i = 0; i < 3; i++)
    {

        if ((board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != 0) || (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != 0))
        {
            return board[i][i]; // Return the player symbol (1 or 2) who won
        }
    }

    // Check diagonals for a win
    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != 0) || (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != 0))
    {
        return board[1][1]; // Return the player symbol (1 or 2) who won
    }

    return 0; // Return 0 if there is no winner yet
}
int checkOver(int board[SQUARE][SQUARE])
{
    for (int i = 0; i < SQUARE; i++)
    {
        for (int j = 0; j < SQUARE; j++)
        {
            if (board[i][j] == 0)
            {
                return 0; // If any cell is empty, the game is not over
            }
        }
    }
    return 1;
}
void inGameScreen()
{
    int menu, moveColumn, moveRow;
    int player = 1;
    int board[3][3] = {0};
    system("clear");
    while (1)
    {

        system("clear");
        printf(" \n=================== Caro =================== \n");
        printf("\n    1   2   3  \n");
        printf("  |---|---|---|\n");

        for (int i = 0; i < 3; i++)
        {
            printf("%d | %s | %s | %s |\n", i + 1,  board[i][0] == 0 ? " " : board[i][0] == 1 ? "X": board[i][0] == 2   ? "O": NULL,
                                                    board[i][1] == 0 ? " " : board[i][1] == 1 ? "X": board[i][1] == 2   ? "O": NULL,
                                                    board[i][2] == 0 ? " " : board[i][2] == 1 ? "X": board[i][2] == 2   ? "O": NULL);
            // printf("%d | %s | %s | %s |\n", i + 1, board[i][0] == 0 ? "0" : board[i][0] == 1 ? "1"
            //                                                             : board[i][0] == 2   ? "2"
            //                                                                                  : NULL,
            //        board[i][1] == 0 ? "0" : board[i][1] == 1 ? "1"
            //                             : board[i][1] == 2   ? "2"
            //                                                  : NULL,
            //        board[i][2] == 0 ? "0" : board[i][2] == 1 ? "1"
            //                             : board[i][2] == 2   ? "2"
            //                                                  : NULL);

            printf("  |---|---|---|\n");
        }
        printf("player %d turn\n", player);
        printf("1. Move \n");
        printf("2. Quit game. \n");
        printf("0. Exit program. \n");
        printf("============================================ \n");
        printf("Enter your choice: ");
        scanf("%d", &menu);
        switch (menu)
        {
        case 1:
            printf("Enter the position you want to move:\n");
            printf(" row   : ");
            if (scanf("%d", &moveRow) != 1 || moveRow > 3 || moveRow < 1)
            {
                printf("Wrong input for row. Please enter a valid integer between 1 and 3.\n");
                clearInputBuffer(); // Clear the input buffer
                getchar();
                break;
            }

            printf(" column: ");
            if (scanf("%d", &moveColumn) != 1 || moveColumn > 3 || moveColumn < 1)
            {
                printf("Wrong input for column. Please enter a valid integer between 1 and 3.\n");
                clearInputBuffer(); // Clear the input buffer
                getchar();
                break;
            }
            if (board[moveRow - 1][moveColumn - 1] != 0)
            {
                printf("This position is already taken. Please choose another one.\n");
                clearInputBuffer(); // Clear the input buffer
                getchar();
                break;
            }
            else
            {
                board[moveRow - 1][moveColumn - 1] = player;
                player = player % 2 ? 2 : 1;
            }
            break;
        case 2:
            system("clear");
            lobbyScreen();
        case 0:
            exit(0);
        default:
            break;
        }
    }
    if (checkOver(board))// if all cell is not empty
    {
        printf("============================================ \n");
        printf("Draw !!!\nEnter to back to lobby screen\n");
        printf("============================================ \n");
        clearInputBuffer(); // Clear the input buffer
        getchar();
        lobbyScreen();
    }
    if (!checkWinner(board)) // if no one win
    {
        printf("============================================ \n");
        printf("Player %d win !!!\nEnter to back to lobby screen\n", checkWinner(board));
        printf("============================================ \n");
        clearInputBuffer(); // Clear the input buffer
        getchar();
        lobbyScreen();
    }
    printf("Enter to back to lobby screen\n");
    clearInputBuffer(); // Clear the input buffer
    getchar();
    lobbyScreen();
}
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
void challengeScreen()
{
    rankingScreen();
    int chossenUser;
    printf("Enter the user ID you want to challenge: ");
    scanf("%d", &chossenUser);
    system("clear");
    printf("Challenge sent to user %d\n", chossenUser);
    printf("Waiting for response from user %d\n", chossenUser);
    // sleep(3);
    inGameScreen();
}
int main()
{
    loginScreen();
}