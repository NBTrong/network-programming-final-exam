// globals.h
#ifndef GLOBALS_H
#define GLOBALS_H

#include <pthread.h>

#define STRING_LENGTH 100

extern char currentUser[STRING_LENGTH];

extern pthread_mutex_t mutex;

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
  CONNECTED_SUCCESSFULLY = 100,

  // Login
  ACCOUNT_EXISTS_AND_ACTIVE = 110,
  ACCOUNT_LOCKED = 211,
  ACCOUNT_NOT_FOUND = 212,
  ACCOUNT_ALREADY_LOGGED_IN = 214,
  ACCOUNT_ALREADY_LOGGED_IN_ANOTHER_DEVICE = 213,

  // Sign up
  ACCOUNT_EXITED = 410,
  SIGN_UP_SUCCESSFULLY = 411,

  // Get list user online
  GET_LIST_USER_ONLINE_SUCCESSFULLY = 511,

  // Logout
  LOGOUT_SUCCESSFULLY = 130,
  UNDEFINED_MESSAGE_TYPE = 300,

  // Do not use the service because not logged in
  NOT_HAVE_ACCESS = 221,
};

enum AccountStatus
{
  BAN = 0,
  ACTIVE = 1
};

#endif
