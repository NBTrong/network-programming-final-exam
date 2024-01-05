#ifndef SCREEN_H
#define SCREEN_H


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "../config/tcp.h"
#include "../utils/utils.h"
#include "../global.h"
#define MAX_LEN 255
#define SQUARE 3
#define BUFFER_SIZE 1024

int checkWinner(int board[SQUARE][SQUARE]);
int checkOver(int board[SQUARE][SQUARE]);

void loginScreen(int client_socket);
void registerScreen(int client_socket);
void rankingScreen(int client_socket);
void challengeScreen(int client_socket);
void readyScreen(int client_socket);
void inGameScreen(int client_socket);
void lobbyScreen(int client_socket);

// void receive_online_session(int client_socket);


#endif // SCREEN_H_INCLUDED