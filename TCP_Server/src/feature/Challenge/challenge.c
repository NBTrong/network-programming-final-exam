#include "challenge.h"

Challenge *challenge_list = NULL;

void challenge_router(int client_socket, const char *message)
{
    char keyword[STRING_LENGTH];
    char parameter[STRING_LENGTH];
    char buffer[STRING_LENGTH];
    sscanf(message, "%s %[^\n]", keyword, parameter);

    if (strcmp(keyword, "SEND") == 0)
    {
        // Send a challenge
        send_challenge(client_socket, parameter);
    }
    else if (strcmp(keyword, "DELETE") == 0)
    {
        // Send a challenge
        delete_challenge(client_socket, parameter);
    }
    else if (strcmp(keyword, "LIST") == 0)
    {
        // Send a challenge
        get_challenged_list(client_socket);
    }
    else
    {
        send_with_error_handling(client_socket, buffer, "300", "Send message failed");
    }
}

void get_challenged_list(int client_socket)
{
    char buffer[STRING_LENGTH];

    Challenge *challenge_list = find_challenge_by_receiver_socket_id(client_socket);
    char response[STRING_LENGTH] = "SUCCESS ";

    if (challenge_list == NULL)
    {
        send_with_error_handling(client_socket,
                                 response,
                                 response,
                                 "Send challenged list error");
        return;
    }
    // Append usernames to the user_list string
    while (challenge_list != NULL)
    {
        strcat(response, challenge_list->sender_username);
        strcat(response, " "); // Add a space to separate usernames
        challenge_list = challenge_list->next;
    }

    // Unlock the mutex after the critical section
    pthread_mutex_unlock(&mutex);

    // Send the list of logged-in users to the client
    send_with_error_handling(client_socket,
                             buffer,
                             response,
                             "Send user list error");
}

void send_challenge(int client_socket, const char *parameter)
{
    char buffer[STRING_LENGTH];
    // Handle parameter get username
    const char *enemy_username = parameter;

    // Get information of client
    Session *client_session = find_session_by_socket_id(client_socket);

    // Check status of enemy
    Session *enemy_session = find_session_by_username(enemy_username);
    if (enemy_session == NULL)
    {
        send_with_error_handling(
            client_socket,
            buffer,
            "ERROR The enemy are not online",
            "Send message failed");
        return;
    }

    // Check players are playing with others
    const Room *enemy_room = find_room_by_socket_id(
        enemy_session->socket_id);
    if (enemy_room != NULL)
    {
        send_with_error_handling(
            client_socket,
            buffer,
            "ERROR The enemy is fighting someone else",
            "Send message failed");
        return;
    }

    // Check rank
    // Get position on the rankings, compare
    // TODO

    // Add challenge to challenge_list
    add_challenge(client_socket,
                  enemy_session->socket_id,
                  client_session->client_username,
                  enemy_session->client_username);

    // Send success to current client
    send_with_error_handling(
        client_socket,
        buffer,
        "SUCCESS Challenge sent successfully, please wait for the enemy to respond",
        "Send message failed");
    return;
}

void add_challenge(
    int sender_socket_id,
    int receiver_socket_id,
    char *sender_username,
    char *receiver_username)
{
    if (find_challenge(sender_socket_id, receiver_socket_id) == NULL)
    {
        pthread_mutex_lock(&mutex);
        Challenge *new_challenge = (Challenge *)malloc(sizeof(Challenge));
        new_challenge->sender_socket_id = sender_socket_id;
        new_challenge->receiver_socket_id = receiver_socket_id;
        strcpy(new_challenge->sender_username, sender_username);
        strcpy(new_challenge->receiver_username, receiver_username);
        new_challenge->next = challenge_list;
        challenge_list = new_challenge;
        pthread_mutex_unlock(&mutex);
    }
}

Challenge *find_challenge(int sender_socket_id, int receiver_socket_id)
{
    pthread_mutex_lock(&mutex);
    Challenge *current = challenge_list;

    while (current != NULL)
    {
        if (current->receiver_socket_id == receiver_socket_id &&
            current->sender_socket_id == sender_socket_id)
        {
            // Return a pointer to the challenge if the socket_id matches
            pthread_mutex_unlock(&mutex);
            return current;
        }

        current = current->next;
    }

    // Return NULL if not found
    pthread_mutex_unlock(&mutex);
    return NULL;
}

Challenge *find_challenge_by_receiver_socket_id(int receiver_socket_id)
{
    pthread_mutex_lock(&mutex);
    Challenge *current = challenge_list;

    while (current != NULL)
    {
        if (current->receiver_socket_id == receiver_socket_id)
        {
            // Return a pointer to the challenge if the socket_id matches
            pthread_mutex_unlock(&mutex);
            return current;
        }

        current = current->next;
    }

    // Return NULL if not found
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void delete_challenge(int client_socket, const char *parameter)
{
    // Lock the mutex before accessing shared data
    pthread_mutex_lock(&mutex);

    // Critical section: update shared data (e.g., session_list)
    Session *current = session_list;
    Session *prev = NULL;

    // Find the session with the given socket_id
    while (current != NULL && strcmp(current->client_username, parameter) != 0)
    {
        prev = current;
        current = current->next;
    }

    // If the session is found, remove it from the linked list
    if (current != NULL)
    {
        if (prev == NULL)
        {
            // The session is the first in the list
            session_list = current->next;
        }
        else
        {
            // The session is in the middle or at the end of the list
            prev->next = current->next;
        }

        // Free the memory for the deleted session
        free(current);
    }

    // Unlock the mutex after critical section
    char buffer[STRING_LENGTH];
    send_with_error_handling(
        client_socket,
        buffer,
        "SUCCESS Remove challenge successfully",
        "Send message failed");

    pthread_mutex_unlock(&mutex);
};