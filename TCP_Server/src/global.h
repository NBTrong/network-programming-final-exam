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

  // Game
  CREATE_GAME_SUCCESSFULLY = 120,
  SEND_GAME_ID_SUCCESSFULLY = 121,
  SEND_USER_TURN_SUCCESSFULLY = 122,
  SEND_BOARD_SUCCESSFULLY = 123,
  SEND_CHALLANGE_SUCCESSFULLY = 124,
  SEND_ACCEPT_CHALLANGE_SUCCESSFULLY = 125,
  SEND_DECLINE_CHALLANGE_SUCCESSFULLY = 126,
  SEND_MOVE_SUCCESSFULLY = 127,
  SEND_WIN_SUCCESSFULLY = 128,
  SEND_LOSE_SUCCESSFULLY = 129,
  

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

enum UserTurn{
  X = 1,
  O = 2
};
enum GameStatus{
  NOT_PLAYING = 0,
  PLAYING = 1,
  BOARD = 3,
  WIN = 4,
  LOSE = 5,
  DRAW = 6
};


#define  ACCOUNT_FILE_PATH "./TCP_Server/database/account.txt"
#define  GAME_LOG_PATH "./TCP_Server/database/log.txt"


#endif
