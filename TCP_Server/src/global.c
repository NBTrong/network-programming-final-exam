#include "global.h"

char currentUser[STRING_LENGTH] = "\0";
int in_game[MAX_CLIENTS];

pthread_mutex_t session_mutex;
pthread_mutex_t challenge_mutex;
pthread_mutex_t socket_mutex;
pthread_mutex_t game_mutex;
pthread_mutex_t room_mutex;
pthread_cond_t cond;