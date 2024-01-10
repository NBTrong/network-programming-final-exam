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

const char *get_code_description(enum Code code);

/**
 * @brief Check the login status for a given client socket.
 *
 * This function checks if a user is currently logged in or not by examining the `currentUser` variable.
 *
 * @param client_socket The socket of the client.
 * @return An integer constant representing the login status (LOGGED_IN or NOT_LOGGED_IN).
 */
int check_login_status(int client_socket);

/**
 * @brief Verify the status of an account in the account.txt file.
 *
 * This function verifies the status of an account by checking the "account.txt" file. If the account
 * is banned or not found, appropriate status codes are returned.
 *
 * @param account A string representing the account to be verified.
 * @return An integer constant representing the account status (ACCOUNT_BANNED, ACCOUNT_VALID, or ACCOUNT_NOT_EXIST).
 */
int verify_account(const char *account);

/**
 * @brief Log in the user.
 *
 * This function allows the user to log in by entering a username. It verifies the account and handles
 * various scenarios, including successful login, banned accounts, and non-existent accounts.
 *
 * @param client_socket The socket of the client.
 * @param username The username entered by the user for login.
 */
void login(int client_socket, const char *username);

/**
 * @brief Log out the user.
 *
 * This function allows the user to log out if they are currently logged in. It clears the `currentUser`
 * variable and logs the logout action.
 *
 * @param client_socket The socket of the client.
 */
void logout(int client_socket);

/**
 * @brief Sign up a new user.
 *
 * This function allows a new user to sign up by entering a username. It verifies if the username
 * is available and adds it to the system if it's not already taken.
 *
 * @param client_socket The socket of the client.
 * @param username The username entered by the user for sign-up.
 */
void sign_up(int client_socket, const char *username);

/**
 * @brief Middleware for authentication.
 *
 * This function acts as a middleware to enforce authentication for accessing certain functionalities.
 * It checks the login status of the client and ensures that only authenticated users can access protected features.
 *
 * @param client_socket The socket of the client.
 * @return An integer constant representing the result of the authentication check.
 */
int auth_middleware(int client_socket);

#endif