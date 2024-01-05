#include <stdio.h>
#include <stdlib.h>

#include "screens.h"
#define SQUARE 3

void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    { /* Clear input buffer */
    }
}
int checkWinner(int board[SQUARE][SQUARE])
{
    // printf("check winner\n");
    // clearInputBuffer(); // Clear the input buffer
    // getchar();
    // Check rows and columns for a win
    for (int i = 0; i < SQUARE; i++)
    {

        if ((board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != 0) || (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != 0))
        {
            printf("checked  winner\n");
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
void inGameScreen(int client_socket)
{
    char buffer[STRING_LENGTH];
    char message[STRING_LENGTH + 5];
    int menu, moveColumn, moveRow;
    int board[3][3] = {0};
    // system("clear");
    // Get user turn
    sprintf(message, "GETUSERTURN");
    printf("\nsent message: '%s'\n", message);
    send_with_error_handling(
        client_socket,
        buffer,
        message,
        "Send message login status error");

    recv_with_error_handling(
        client_socket,
        buffer,
        sizeof(buffer),
        "Error receiving data from the client");

    int player = atoi(buffer);
    while (1)
    {

        printf(" \n=================== Caro =================== \n");
        printf("\n  1   2   3  \n");
        printf("|---|---|---|\n");

        for (int i = 0; i < SQUARE; i++)
        {
            printf("| %s | %s | %s |\n",
                   board[i][0] == 0 ? " " : board[i][0] == 1 ? "X"
                                        : board[i][0] == 2   ? "O"
                                                             : NULL,
                   board[i][1] == 0 ? " " : board[i][1] == 1 ? "X"
                                        : board[i][1] == 2   ? "O"
                                                             : NULL,
                   board[i][2] == 0 ? " " : board[i][2] == 1 ? "X"
                                        : board[i][2] == 2   ? "O"
                                                             : NULL);
            printf("|---|---|---|\n");
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
            printf("From 1-9 enter the position you want to move:\n");
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
                printf("Wrong input for column. Please press enter and enter a valid integer between 1 and 3.\n");
                clearInputBuffer(); // Clear the input buffer
                getchar();
                break;
            }
            if (board[moveRow - 1][moveColumn - 1] != 0)
            {
                printf("This position is already taken. Please press enter and choose another move.\n");
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
            lobbyScreen(client_socket);
            break;
        case 0:
            exit(0);
        default:
            break;
        }
        if (checkOver(board)) // if all cell is not empty
        {
            printf("============================================ \n");
            printf("Draw !!!\nEnter to back to lobby screen\n");
            printf("============================================ \n");
            clearInputBuffer(); // Clear the input buffer
            getchar();
            lobbyScreen(client_socket);
        }
        if (checkWinner(board) != 0) // if no one win
        {
            printf("============================================ \n");
            printf("Player %d win !!!\nEnter to back to lobby screen\n", checkWinner(board));
            printf("============================================ \n");
            clearInputBuffer(); // Clear the input buffer
            getchar();
            lobbyScreen(client_socket);
        }
    }
    printf("Enter to back to lobby screen\n");
    clearInputBuffer(); // Clear the input buffer
    getchar();
    lobbyScreen(client_socket);
}
