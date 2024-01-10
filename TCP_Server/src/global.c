#include "global.h"

char currentUser[STRING_LENGTH] = "\0";
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int in_game[MAX_CLIENTS];
pthread_mutex_t socket_mutex;
pthread_cond_t cond;