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
        send_challenge(client_socket, parameter);
        print_challenge_list();
    }
    else if (strcmp(keyword, "CANCEL") == 0)
    {
        handle_cancel_challenge(client_socket, parameter);
        print_challenge_list();
    }
    else if (strcmp(keyword, "LIST") == 0)
    {
        get_challenged_list(client_socket);
        print_challenge_list();
    }
    else if (strcmp(keyword, "REJECT") == 0)
    {
        handle_reject_challenge(client_socket, parameter);
    }
    else if (strcmp(keyword, "ACCEPT") == 0)
    {
        handle_accept_challenge(client_socket, parameter);
        printf_room_list();
        printf("\n\n");
        print_challenge_list();
    }
    else
    {
        send_with_error_handling(client_socket, buffer, "300", "Send message failed");
    }
}

// --------------------------- Services ---------------------------

void get_challenged_list(int client_socket)
{
    Challenge *result_head = NULL;
    Challenge *result_tail = NULL;

    // Traverse the linked list
    pthread_mutex_lock(&mutex);
    Challenge *current = challenge_list;
    while (current != NULL)
    {
        // Check if the element satisfies the condition
        if (current->receiver_socket_id == client_socket)
        {
            // Create a copy of the element to add to the result list
            Challenge *new_challenge = (Challenge *)malloc(sizeof(Challenge));
            memcpy(new_challenge, current, sizeof(Challenge));
            new_challenge->next = NULL;

            // If the result list is not initialized, initialize it
            if (result_head == NULL)
            {
                result_head = new_challenge;
                result_tail = new_challenge;
            }
            else
            {
                // Add the element to the end of the result list
                result_tail->next = new_challenge;
                result_tail = new_challenge;
            }
        }

        current = current->next;
    }

    pthread_mutex_unlock(&mutex);

    char buffer[STRING_LENGTH];
    char response[STRING_LENGTH] = "SUCCESS ";
    current = result_head;

    while (current != NULL)
    {
        if (current->receiver_socket_id == client_socket)
        {
            strcat(response, current->sender_username);
            strcat(response, " "); // Add a space to separate usernames
        }

        current = current->next;
    }

    send_with_error_handling(client_socket,
                             buffer,
                             response,
                             "Send user list error");
}

typedef struct
{
    char username[50];
    int is_blocked;
    int score;
} Player;

int compare_players(const void *a, const void *b)
{
    return ((Player *)a)->score - ((Player *)b)->score;
}

int find_player_rank(Player players[], int num_players, const char *username)
{
    for (int i = 0; i < num_players; i++)
    {
        if (strcmp(players[i].username, username) == 0)
        {
            return i + 1; // Rank is 1-indexed
        }
    }
    return -1; // Player not found
}

int check_rank_difference(const char *username1, const char *username2)
{
    // Read file
    FILE *file = fopen("./TCP_Server/database/account.txt", "r"); // Open the file in read mode ("r")

    if (file == NULL)
    {
        printf("Unable to open the file.\n");
        exit(1); // Exit the program with an error code
    }

    char line[MAX_LINE_LENGTH];
    char test0[STRING_LENGTH];
    int test1, test2;
    Player players[MAX_PLAYERS];
    int num_players = 0;

    // Read players from the file
    while (fscanf(file, "%s %d %d", players[num_players].username, &players[num_players].is_blocked, &players[num_players].score) == 3)
    {
        num_players++;
        if (num_players >= MAX_PLAYERS)
        {
            fprintf(stderr, "Too many players in the file. Increase MAX_PLAYERS.\n");
            fclose(file);
            exit(EXIT_FAILURE);
        }
    }

    // Sort players based on score
    qsort(players, num_players, sizeof(Player), compare_players);

    // Find ranks of the two players
    int rank1 = find_player_rank(players, num_players, username1);
    int rank2 = find_player_rank(players, num_players, username2);

    printf("User1 rank: %d, user2 rank: %d\n", rank1, rank2);

    // Calculate rank difference and return the result
    int rank_difference = abs(rank1 - rank2);

    // Close the file before returning
    fclose(file);

    return rank_difference;
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

    if (enemy_session->socket_id == client_socket)
    {
        send_with_error_handling(
            client_socket,
            buffer,
            "ERROR You can't challenge yourself",
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
    int rank_difference = check_rank_difference(client_session->client_username, enemy_session->client_username);
    if (rank_difference > 10)
    {
        send_with_error_handling(
            client_socket,
            buffer,
            "ERROR The ranking difference is too big, challenge others",
            "Send message failed");
        return;
    }
    printf("The rank difference is: %d\n", rank_difference);

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

void handle_cancel_challenge(int client_socket, char *enemy_username)
{
    char buffer[STRING_LENGTH];

    // Lock the mutex before accessing shared data
    pthread_mutex_lock(&mutex);

    Challenge *current = challenge_list;
    Challenge *prev = NULL;

    while (current != NULL && current->sender_socket_id != client_socket &&
           strcmp(current->receiver_username, enemy_username) != 0)
    {
        prev = current;
        current = current->next;
    }

    if (current != NULL)
    {
        if (prev == NULL)
        {
            challenge_list = current->next;
        }
        else
        {
            prev->next = current->next;
        }
        free(current);
        send_with_error_handling(
            client_socket,
            buffer,
            "SUCCESS Cancel challenge success",
            "Send message failed");
    }
    else
    {
        send_with_error_handling(
            client_socket,
            buffer,
            "ERROR Cancel challenge failed",
            "Send message failed");
    }

    pthread_mutex_unlock(&mutex);
}

void handle_reject_challenge(int client_socket, char *sender_username)
{
    char buffer[STRING_LENGTH];

    pthread_mutex_lock(&mutex);

    // ---------------------------- Remove challenge ----------------------------
    Challenge *current = challenge_list;
    Challenge *prev = NULL;

    while (current != NULL &&
           (current->receiver_socket_id != client_socket ||
            strcmp(current->sender_username, sender_username) != 0))
    {
        prev = current;
        current = current->next;
    }
    // Challenge not existed
    if (current == NULL)
    {
        send_with_error_handling(client_socket,
                                 buffer,
                                 "ERROR This challenge has been canceled or does not exist",
                                 "Send error");
        pthread_mutex_unlock(&mutex);
        return;
    }
    // Remove challenge
    if (prev == NULL)
    {
        // The challenge to be removed is at the beginning of the list
        challenge_list = current->next;
    }
    else
    {
        // The challenge to be removed is not at the beginning of the list
        prev->next = current->next;
    }
    int sender_socket_id = current->sender_socket_id;
    free(current);
    pthread_mutex_unlock(&mutex);

    // Notification to client
    send_with_error_handling(client_socket,
                             buffer,
                             "SUCCESS Cancel challenge successfully",
                             "Send error");

    send_with_error_handling(sender_socket_id,
                             buffer,
                             "ERROR Enemy reject challenge",
                             "Send error");
}

void handle_accept_challenge(int client_socket, char *sender_username)
{
    char buffer[STRING_LENGTH];
    pthread_mutex_lock(&mutex);
    Challenge *current = challenge_list;
    Challenge *prev = NULL;

    while (current != NULL)
    {
        if ((current->receiver_socket_id == client_socket) &&
            strcmp(current->sender_username, sender_username) == 0)
        {
            // Challenge found, break out of the loop
            break;
        }

        prev = current;
        current = current->next;
    }

    if (current == NULL)
    {
        // Challenge not existed
        pthread_mutex_unlock(&mutex);
        send_with_error_handling(client_socket,
                                 buffer,
                                 "ERROR This challenge not existed",
                                 "Send error");
        return;
    }

    // Remove challenge from the challenge_list
    if (prev == NULL)
    {
        // The challenge to be removed is at the beginning of the list
        challenge_list = current->next;
    }
    else
    {
        // The challenge to be removed is not at the beginning of the list
        prev->next = current->next;
    }

    pthread_mutex_unlock(&mutex);

    // Add users to the room
    send_to_queue(add_room(current->sender_socket_id,
                           current->receiver_socket_id,
                           current->sender_username,
                           current->receiver_username));

    // Send success message to the client
    send_with_error_handling(client_socket,
                             buffer,
                             "SUCCESS Start game",
                             "Send error");

    send_with_error_handling(current->sender_socket_id,
                             buffer,
                             "SUCCESS Start game",
                             "Send error");

    // Free the memory of the removed challenge node
    free(current);
}

// --------------------------- Support function ---------------------------------

void add_challenge(
    int sender_socket_id,
    int receiver_socket_id,
    char *sender_username,
    char *receiver_username)
{
    if (find_challenge(sender_socket_id, receiver_socket_id) != NULL)
        return;
    pthread_mutex_lock(&mutex);
    Challenge *new_challenge = (Challenge *)malloc(sizeof(Challenge));
    new_challenge->sender_socket_id = sender_socket_id;
    new_challenge->receiver_socket_id = receiver_socket_id;
    strcpy(new_challenge->sender_username, sender_username);
    strcpy(new_challenge->receiver_username, receiver_username);
    new_challenge->next = challenge_list;
    challenge_list = new_challenge;
    printf("Add nè: %s\n", challenge_list->sender_username);
    pthread_mutex_unlock(&mutex);
}

Challenge *find_challenge(int sender_socket_id, int receiver_socket_id)
{
    pthread_mutex_lock(&mutex);
    Challenge *current = challenge_list;

    while (current != NULL)
    {
        if ((current->receiver_socket_id == receiver_socket_id) &&
            (current->sender_socket_id == sender_socket_id))
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

void print_challenge_list()
{
    Challenge *current = challenge_list;

    // Traverse the linked list and print sender and receiver names
    while (current != NULL)
    {
        printf("Sender: %s, Receiver: %s\n", current->sender_username, current->receiver_username);
        current = current->next;
    }
}

void printf_room_list()
{
    Room *current = room_list;

    // Traverse the linked list and print sender and receiver names
    while (current != NULL)
    {
        printf("Sender: %s, Receiver: %s\n", current->sender_username, current->receiver_username);
        current = current->next;
    }
}

void delete_challenges_by_receiver_socket_id(int socket_id)
{
    pthread_mutex_lock(&mutex);
    Challenge *current = challenge_list;
    Challenge *prev = NULL;
    char buffer[STRING_LENGTH];

    // Traverse the challenge list
    while (current != NULL)
    {
        // If the receiver_socket_id of the node is equal to socket_id, delete that node
        if (current->receiver_socket_id == socket_id)
        {
            send_with_error_handling(current->sender_socket_id,
                                     buffer,
                                     "ERROR Enemy disconnect",
                                     "Send error");
            if (prev == NULL)
            {
                // If the node to be deleted is the first node
                Challenge *temp = current;
                challenge_list = current->next;
                current = current->next;
                free(temp);
            }
            else
            {
                // If the node to be deleted is not the first node
                Challenge *temp = current;
                prev->next = current->next;
                current = current->next;
                free(temp);
            }
        }
        else
        {
            // If it's not the node to be deleted, move to the next node
            prev = current;
            current = current->next;
        }
    }
    pthread_mutex_unlock(&mutex);
}

void delete_challenges_by_sender_socket_id(int socket_id)
{
    pthread_mutex_lock(&mutex);
    Challenge *current = challenge_list;
    Challenge *prev = NULL;

    // Traverse the challenge list
    while (current != NULL)
    {
        // If the receiver_socket_id of the node is equal to socket_id, delete that node
        if (current->sender_socket_id == socket_id)
        {
            if (prev == NULL)
            {
                // If the node to be deleted is the first node
                Challenge *temp = current;
                challenge_list = current->next;
                current = current->next;
                free(temp);
            }
            else
            {
                // If the node to be deleted is not the first node
                Challenge *temp = current;
                prev->next = current->next;
                current = current->next;
                free(temp);
            }
        }
        else
        {
            // If it's not the node to be deleted, move to the next node
            prev = current;
            current = current->next;
        }
    }
    pthread_mutex_unlock(&mutex);
}
