#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define MAX_LEN 255
#define SQUARE 3

int checkWinner(int board[SQUARE][SQUARE]);
int checkOver(int board[SQUARE][SQUARE]);
void loginScreen();
void registerScreen();
void lobbyScreen();
void readyScreen();
void inGameScreen();
void rankingScreen();
void challengeScreen();


void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    { /* Clear input buffer */
    }
}

#include "loginScreen.c"
#include "registerScreen.c"
#include "rankingScreen.c"
#include "challengeScreen.c"
#include "readyScreen.c"
#include "lobbyScreen.c"
#include "inGameScreen.c"
