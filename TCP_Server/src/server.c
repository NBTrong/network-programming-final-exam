#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/select.h>

#include "global.h"
#include "./config/tcp.h"
#include "./feature/Auth/auth.h"
#include "./feature/Session/session.h"
#include "./feature/Challenge/challenge.h"

void router(int client_socket, const char *message);
void *handle_apis(void *arg);
void *games_controller(void *arg);
void init_game(void *arg);

int main(int argc, char *argv[])
{
    // Handle argv
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s [Port_Number]\n", argv[0]);
        exit(1);
    }
    int port_number = atoi(argv[1]);

    // Init multi thread
    pthread_t tid;
    pthread_create(&tid, NULL, &games_controller, NULL);

    // Init socket mutex
    pthread_mutex_init(&socket_mutex, NULL);
    pthread_cond_init(&cond, NULL);
    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        in_game[i] = 0;
    }

    // Init server
    int server_socket = init_server(port_number);

    // Communicate with clients
    int *client_socket;
    struct sockaddr_in client_addr;
    socklen_t client_len;
    client_len = sizeof(client_addr);
    while (1)
    {
        client_socket = (int *)malloc(sizeof(int));
        // Accept connect with client
        *client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
        if (*client_socket < 0)
        {
            perror("Error accepting connection");
            continue;
        }

        // Create thread
        pthread_create(&tid, NULL, &handle_apis, client_socket);
    }

    // Close server
    close(server_socket);
    return 0;
}

// ------------------- HANDLE GAME --------------------

void *games_controller(void *arg)
{
    Message message;

    key_t key;
    int msgid;

    // ftok to generate unique key
    key = ftok("20194693", 65);

    // msgget creates a message queue
    msgid = msgget(key, 0666 | IPC_CREAT);
    message.mess_type = 1;

    while (msgrcv(msgid, &message, sizeof(message.room_data), 1, 0) != -1)
    {
        // Process the received message
        printf("Received Message: Sender Socket ID: %d, Receiver Socket ID: %d, Sender username: %s, Receiver username: %s\n",
               message.room_data.sender_socket_id, message.room_data.receiver_socket_id, message.room_data.sender_username, message.room_data.receiver_username);

        // Create a new thread to handle the room associated with the message
        pthread_t room_thread;
        pthread_create(&room_thread, NULL, init_game, (void *)&message.room_data);
    }
}

void init_game(void *arg)
{
    Room *room = (Room *)arg;

    pthread_mutex_lock(&socket_mutex);
    in_game[room->sender_socket_id] = 1;
    in_game[room->receiver_socket_id] = 1;
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&socket_mutex);

    game(room->sender_socket_id, room->receiver_socket_id);

    remove_room(room->sender_socket_id,
                room->receiver_socket_id,
                room->sender_username,
                room->receiver_username);

    pthread_mutex_lock(&socket_mutex);
    in_game[room->sender_socket_id] = 0;
    in_game[room->receiver_socket_id] = 0;
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&socket_mutex);
};

// ------------------- HANDLE APIs --------------------

void *handle_apis(void *arg)
{
    int client_socket = *(int *)arg;
    char send_message[STRING_LENGTH];
    char recv_message[STRING_LENGTH];

    free(arg);

    printf("Client %d request connect\n", client_socket);
    send_with_error_handling(client_socket,
                             send_message,
                             get_code_description(CONNECTED_SUCCESSFULLY),
                             "Send message failed");

    fd_set read_fds;
    struct timeval tv;
    int retval;

    while (1)
    {
        FD_ZERO(&read_fds);
        FD_SET(client_socket, &read_fds);

        tv.tv_sec = 1;
        tv.tv_usec = 0;

        retval = select(client_socket + 1, &read_fds, NULL, NULL, &tv);

        if (retval == 0)
        {
            // Check if the client is currently in a game
            pthread_mutex_lock(&socket_mutex);
            while (in_game[client_socket])
            {
                printf("IN game %d %d\n", in_game[client_socket], client_socket);
                // Wait here if the client is in a game
                pthread_cond_wait(&cond, &socket_mutex);
            }
            pthread_mutex_unlock(&socket_mutex);
        }

        if (retval == -1)
        {
            perror("select()");
            break;
        }

        if (FD_ISSET(client_socket, &read_fds))
        {
            if (!recv_with_error_handling(client_socket, recv_message, sizeof(recv_message), "Error receiving data from the client"))
            {
                break;
            }
            router(client_socket, recv_message);
        }
    }

    delete_session_by_socket_id(client_socket);

    return 0;
}

void router(int client_socket, const char *message)
{
    printf("Recv from client %d: %s\n", client_socket, message);
    char keyword[STRING_LENGTH];
    char parameter[STRING_LENGTH];
    char buffer[STRING_LENGTH];
    sscanf(message, "%s %[^\n]", keyword, parameter);

    if (strcmp(keyword, "USER") == 0)
    {
        login(client_socket, parameter);
    }
    else if (strcmp(keyword, "SIGNUP") == 0)
    {
        sign_up(client_socket, parameter);
    }
    else if (strcmp(keyword, "ONLINE") == 0)
    {
        if (!auth_middleware(client_socket))
            return;
        send_all_sessions(client_socket);
    }
    else if (strcmp(keyword, "CHALLENGE") == 0)
    {
        if (!auth_middleware(client_socket))
            return;
        challenge_router(client_socket, parameter);
    }
    else if (strcmp(keyword, "BYE") == 0)
    {
        if (!auth_middleware(client_socket))
            return;
        logout(client_socket);
    }
    else
    {
        send_with_error_handling(client_socket, buffer, "300", "Send message failed");
    }
};
