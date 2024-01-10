#ifndef AUTH_H
#define AUTH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "../../global.h"
#include "../Session/session.h"
#include "../../utils/utils.h"
#include "../../config/tcp.h"
#include "../Challenge/challenge.h"

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

/**
 * @brief Get the description of a message code.
 *
 * This function returns the description of a message code.
 *
 * @param code The message code.
 * @return The description of the message code.
 */
const char *get_code_description(enum Code code);

/**
 * @brief Check the login status of a client.
 *
 * This function checks whether a client is logged in or not.
 *
 * @param client_socket The client socket.
 * @return NOT_LOGGED_IN if not logged in, LOGGED_IN if logged in.
 */
int check_login_status(int client_socket);

/**
 * @brief Verify an account's validity.
 *
 * This function verifies the validity of an account based on the account's status.
 *
 * @param account The account username to verify.
 * @return ACCOUNT_BANNED if the account is banned, ACCOUNT_VALID if the account is active, ACCOUNT_NOT_EXIST if the account does not exist.
 */
int verify_account(const char *account);

/**
 * @brief Check if an account exists.
 *
 * This function checks if an account with the given username exists.
 *
 * @param username The username to check.
 * @return 1 if the account exists, 0 if it does not.
 */
int check_account_existence(const char *username);

/**
 * @brief Handle the login process.
 *
 * This function handles the login process for a client.
 *
 * @param client_socket The client socket.
 * @param username The username to log in.
 */
void login(int client_socket, const char *username);

/**
 * @brief Handle the logout process.
 *
 * This function handles the logout process for a client.
 *
 * @param client_socket The client socket.
 */
void logout(int client_socket);

/**
 * @brief Handle the sign-up process.
 *
 * This function handles the sign-up process for a client.
 *
 * @param client_socket The client socket.
 * @param username The username to sign up.
 */
void sign_up(int client_socket, const char *username);

/**
 * @brief Middleware for authentication.
 *
 * This function acts as a middleware to check if a client is authenticated (logged in).
 *
 * @param client_socket The client socket.
 * @return 1 if authenticated, 0 if not authenticated.
 */
int auth_middleware(int client_socket);

#endif