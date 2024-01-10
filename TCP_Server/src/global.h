// globals.h
#ifndef GLOBALS_H
#define GLOBALS_H

#include <pthread.h>

#define STRING_LENGTH 100
#define MAX_CLIENTS 100

#define MAX_LINE_LENGTH 1000
#define MAX_PLAYERS 1000

extern char currentUser[STRING_LENGTH];
extern int msgid;

extern pthread_mutex_t session_mutex;
extern pthread_mutex_t challenge_mutex;
extern pthread_mutex_t game_mutex;
extern pthread_mutex_t room_mutex;
extern pthread_mutex_t socket_mutex;
extern pthread_cond_t cond;

extern const char *messageCodes[];
extern int in_game[MAX_CLIENTS];

#endif
