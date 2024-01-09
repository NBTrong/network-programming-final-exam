#include "auth.h"

int check_login_status(int client_socket)
{
    Session *session = find_session_by_socket_id(client_socket);
    if (session == NULL)
        return NOT_LOGGED_IN;

    return LOGGED_IN;
};

// --------------------------------------- Login function ----------------------------------------------

int verify_account(const char *account)
{
    // Read file
    FILE *file = fopen("./TCP_Server/database/account.txt", "r"); // Open the file in read mode ("r")

    if (file == NULL)
    {
        printf("Unable to open the file.\n");
        exit(1); // Exit the program with an error code
    }

    char username[STRING_LENGTH]; // Variable to store the username
    int status;                   // Variable to store the status
    int point;

    // Read and display information from the file
    while (fscanf(file, "%s %d %d", username, &status, &point) == 3)
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

int check_account_existence(const char *username)
{
    FILE *file = fopen("./TCP_Server/database/account.txt", "r");
    if (file == NULL)
    {
        perror("Error opening database file");
        exit(EXIT_FAILURE);
    }

    char line[STRING_LENGTH];
    while (fgets(line, sizeof(line), file))
    {
        char storedUsername[STRING_LENGTH];
        int status;
        int point;

        if (sscanf(line, "%s %d %d", storedUsername, &status, &point) == 3)
        {
            if (strcmp(username, storedUsername) == 0)
            {
                fclose(file);
                return 1; // Account exited
            }
        }
    }

    fclose(file);
    return 0; // Account not exited
}

void sign_up(int client_socket, const char *username)
{
    char buffer[STRING_LENGTH];

    // Check the client's login status
    if (check_login_status(client_socket) == LOGGED_IN)
    {
        send_with_error_handling(
            client_socket,
            buffer,
            get_code_description(ACCOUNT_ALREADY_LOGGED_IN),
            "Send message login status error");
        return;
    }

    // Check account exited in file
    if (check_account_existence(username) == 1)
    {
        send_with_error_handling(
            client_socket,
            buffer,
            get_code_description(ACCOUNT_EXITED),
            "Send message login status error");
        return;
    }

    FILE *file = fopen("./TCP_Server/database/account.txt", "a");
    if (file == NULL)
    {
        perror("Error opening database file");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s 1 0\n", username);
    send_with_error_handling(
        client_socket,
        buffer,
        get_code_description(SIGN_UP_SUCCESSFULLY),
        "Send message login status error");
    fclose(file);
};

void login(int client_socket, const char *username)
{
    char buffer[STRING_LENGTH];

    // Check the client's login status
    if (check_login_status(client_socket) == LOGGED_IN)
    {
        send_with_error_handling(
            client_socket,
            buffer,
            get_code_description(ACCOUNT_ALREADY_LOGGED_IN),
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
            get_code_description(ACCOUNT_ALREADY_LOGGED_IN_ANOTHER_DEVICE),
            "Send message login status error");
        return;
    }

    // Verify account
    int result = verify_account(username);
    switch (result)
    {
    case ACCOUNT_BANNED:
        send_with_error_handling(
            client_socket,
            buffer,
            get_code_description(ACCOUNT_LOCKED),
            "Send message login status error");
        break;

    case ACCOUNT_NOT_EXIST:
        send_with_error_handling(
            client_socket,
            buffer,
            get_code_description(ACCOUNT_NOT_FOUND),
            "Send message login status error");
        break;

    case ACCOUNT_VALID:
        // Account valid, create session and login
        add_session(client_socket, "", 0, username);
        send_with_error_handling(
            client_socket,
            buffer,
            get_code_description(ACCOUNT_EXISTS_AND_ACTIVE),
            "Send message login status error");
        // print_all_sessions();
        break;
    }
}

// --------------------------------------- Logout function ---------------------------------------------

void logout(int client_socket)
{
    char buffer[STRING_LENGTH];
    delete_session_by_socket_id(client_socket);
    send_with_error_handling(
        client_socket,
        buffer,
        get_code_description(LOGOUT_SUCCESSFULLY),
        "Send message login status error");
};

int auth_middleware(int client_socket)
{
    char buffer[STRING_LENGTH];
    if (check_login_status(client_socket) == NOT_LOGGED_IN)
    {
        send_with_error_handling(
            client_socket,
            buffer,
            get_code_description(NOT_HAVE_ACCESS),
            "Send message login status error");
        return 0;
    }

    return 1;
}
