#include "auth.h"

int checkLoginStatus(int client_socket)
{
    Session *session = find_session_by_socket_id(client_socket);
    if (session == NULL)
        return NOT_LOGGED_IN;

    return LOGGED_IN;
};

// --------------------------------------- Login function ----------------------------------------------

int verifyAccount(const char *account)
{
    // Read file
    FILE *file = fopen(ACCOUNT_FILE_PATH, "r"); // Open the file in read mode ("r")

    if (file == NULL)
    {
        printf("Unable to open the file.\n");
        exit(1); // Exit the program with an error code
    }

    char username[STRING_LENGTH]; // Variable to store the username
    int status;                   // Variable to store the status

    // Read and display information from the file
    while (fscanf(file, "%s %d", username, &status) == 2)
    {
        // Banned account
        if (strcmp(account, username) == 0 && status == BAN)
        {
            return ACCOUNT_BANNED;
        }

        // Valid account
        if (strcmp(account, username) == 0 && status == ACTIVE)
        {
            return ACCOUNT_VALID;
        }
    }

    fclose(file); // Close the file after usage

    return ACCOUNT_NOT_EXIST;
};

void login(int client_socket, const char *username)
{
    char buffer[STRING_LENGTH];

    // Check the client's login status
    if (checkLoginStatus(client_socket) == LOGGED_IN)
    {
        send_with_error_handling(
            client_socket,
            buffer,
            int_to_string(ACCOUNT_ALREADY_LOGGED_IN),
            "Send message login status error");
        return;
    }

    // Check account's login status on other devices
    Session *session = find_session_by_username(username);
    if (session != NULL && session->socket_id != client_socket)
    {

        send_with_error_handling(
            client_socket,
            buffer,
            int_to_string(ACCOUNT_ALREADY_LOGGED_IN_ANOTHER_DEVICE),
            "Send message login status error");
        return;
    }

    // Verify account
    int result = verifyAccount(username);
    switch (result)
    {
    case ACCOUNT_BANNED:
        send_with_error_handling(
            client_socket,
            buffer,
            int_to_string(ACCOUNT_LOCKED),
            "Send message login status error");
        break;

    case ACCOUNT_NOT_EXIST:
        send_with_error_handling(
            client_socket,
            buffer,
            int_to_string(ACCOUNT_NOT_FOUND),
            "Send message login status error");
        break;

    case ACCOUNT_VALID:
        // Account valid, create session and login
        add_session(client_socket, "", 0, username, LOGGED_IN);
        send_with_error_handling(
            client_socket,
            buffer,
            int_to_string(ACCOUNT_EXISTS_AND_ACTIVE),
            "Send message login status error");
        // print_all_sessions();
        break;
    }
}

// --------------------------------------- Logout function ---------------------------------------------

void logout(int client_socket)
{
    char buffer[STRING_LENGTH];

    int result = checkLoginStatus(client_socket);
    switch (result)
    {
    case LOGGED_IN:
        delete_session_by_socket_id(client_socket);
        send_with_error_handling(
            client_socket,
            buffer,
            int_to_string(LOGOUT_SUCCESSFULLY),
            "Send message login status error");
        break;

    case NOT_LOGGED_IN:
        send_with_error_handling(
            client_socket,
            buffer,
            int_to_string(NOT_HAVE_ACCESS),
            "Send message login status error");
        break;

    default:
        break;
    }
}