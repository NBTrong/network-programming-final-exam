#include "global.h"

char currentUser[STRING_LENGTH] = "\0";
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int in_game[MAX_CLIENTS];
pthread_mutex_t socket_mutex;
pthread_cond_t cond;

const char *messageCodes[] = {
    // Connect
    "SUCCESS Connect successfully",

    // Login
    "SUCCESS Login successfully",
    "ERROR Account locked",
    "ERROR Account not found",
    "ERROR Account already logged in",
    "ERROR Account already logged in on another device",

    // Sign up
    "ERROR Account exited",
    "SUCCESS Sign up successfully",

    // Get users online
    "SUCCESS Get list of online users",

    // Logout
    "SUCCESS Logout successfully",

    // Error type message
    "ERROR Undefined message type",

    // 401
    "ERROR Do not have access"};

const char *get_code_description(enum Code code)
{
  return messageCodes[code];
}