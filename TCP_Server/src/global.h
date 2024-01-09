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
extern pthread_mutex_t mutex;
extern pthread_mutex_t socket_mutex;
extern pthread_cond_t cond;
extern const char *messageCodes[];
extern int in_game[MAX_CLIENTS];

enum AccountStatus
{
  BAN = 0,
  ACTIVE = 1
};

enum LoginStatus
{
  ACCOUNT_NOT_EXIST = 1,
  ACCOUNT_BANNED = 2,
  LOGGED_IN = 3,
  NOT_LOGGED_IN = 4,
  ACCOUNT_VALID = 5,
  LOGGED_IN_ON_ANOTHER_DEVICE = 6
};

enum Code
{
  // Connect server
  CONNECTED_SUCCESSFULLY,

  // Login
  ACCOUNT_EXISTS_AND_ACTIVE,
  ACCOUNT_LOCKED,
  ACCOUNT_NOT_FOUND,
  ACCOUNT_ALREADY_LOGGED_IN,
  ACCOUNT_ALREADY_LOGGED_IN_ANOTHER_DEVICE,

  // Sign up
  ACCOUNT_EXITED,
  SIGN_UP_SUCCESSFULLY,

  // Get list user online
  GET_LIST_USER_ONLINE_SUCCESSFULLY,

  // Logout
  LOGOUT_SUCCESSFULLY,

  // Error type message
  UNDEFINED_MESSAGE_TYPE,

  // Do not use the service because not logged in
  NOT_HAVE_ACCESS,
};

const char *get_code_description(enum Code code);

#endif
