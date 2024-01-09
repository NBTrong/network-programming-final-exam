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

/**
 * @brief Check the login status.
 *
 * This function checks if a user is currently logged in or not by examining the `currentUser` variable.
 *
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
 */
void login(int client_socket, const char *username);

/**
 * @brief Log out the user.
 *
 * This function allows the user to log out if they are currently logged in. It clears the `currentUser`
 * variable and logs the logout action.
 */
void logout(int client_socket);

void sign_up(int client_socket, const char *username);

int auth_middleware(int client_socket);

#endif