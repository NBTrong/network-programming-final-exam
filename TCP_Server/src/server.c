#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>

#include "global.h"
#include "./config/tcp.h"
#include "./feature/Auth/auth.h"
#include "./feature/Session/session.h"
#include "./feature/GameHandler/gameHandler.h"

void router(int client_socket, const char *message);
void *handleClient(void *arg);

int userTurn = X;

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
        pthread_create(&tid, NULL, &handleClient, client_socket);
    }

    // Close server
    close(server_socket);
    return 0;
}

void *handleClient(void *arg)
{
    int client_socket = *(int *)arg;
    char sendMessage[STRING_LENGTH];
    char recvMessage[STRING_LENGTH];

    printf("Client %d request connect\n", client_socket);
    send_with_error_handling(client_socket, sendMessage, int_to_string(CONNECTED_SUCCESSFULLY), "Send message failed");
    while (recv_with_error_handling(
        client_socket,
        recvMessage,
        sizeof(recvMessage),
        "Error receiving data from the client"))
    {
        router(client_socket, recvMessage);
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
    int client_send_challange_socket, client_receive_challange_socket;
    sscanf(message, "%s %[^\n]", keyword, parameter);

    if (strcmp(keyword, "USER") == 0)
    {
        printf("parameter: '%s'\n", parameter);
        login(client_socket, parameter);
    }
    else if (strcmp(keyword, "BYE") == 0)
    {
        logout(client_socket);
    }
    else if (strcmp(keyword, "SENDCHALLANGE") == 0)
    {
        printf("chanlange from %d to '%s'\n",client_socket, parameter);
        client_send_challange_socket = client_socket;
        // client_receive_challange_socket = find_session_by_username(parameter)->socket_id;
        client_receive_challange_socket = atoi(parameter);
        printf("client_send_challange_socket: %d\n", client_send_challange_socket);
        printf("client_receive_challange_socket: %d\n", client_receive_challange_socket);
        // sendChallange(client_socket, parameter);

        createNewGame(client_send_challange_socket,client_receive_challange_socket,1);
    }
    else if (strcmp(keyword, "GETUSERTURN") == 0)
    {
        printf("RECEIVECHALLANGE\n");
    }
    else if (strcmp(keyword, "ACCEPT") == 0)
    {
        printf("ACCEPT\n");
    }
    else if (strcmp(keyword, "REJECT") == 0)
    {
        printf("REJECT\n");
    }
    // else if (strcmp(keyword, "ACCEPT") == 0)
    // {
    // }
    // else if (strcmp(keyword, "REJECT") == 0)
    // {
    //     rejectChallange(client_socket, parameter);
    // }
    else if (strcmp(keyword, "MOVE") == 0)
    {
        printf("MOVE\n");
    }
    else
    {
        send_with_error_handling(client_socket, buffer, "300", "Send message failed");
    }
};
