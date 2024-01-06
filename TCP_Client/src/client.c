#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <libgen.h>
#include "./utils/utils.h"
#include "./config/menu.h"
#include "./feature/Auth/auth.h"
#include "./feature/Article/article.h"
#include "./feature/Request/request.h"

pthread_mutex_t lock;

void *server_response_handler(void *socket)
{
    int sockfd = *(int *)socket;

    while (1)
    {
        char buffer[STRING_LENGTH];
        recv_with_error_handling(
            sockfd,
            buffer,
            sizeof(buffer),
            "Error receiving data from the client");

        pthread_mutex_lock(&lock);
        printStatusMessage(buffer, sockfd);
        if (strncmp(buffer, "RECV_REQUEST", strlen("RECV_REQUEST")) != 0)
        {
            isResponse = 1;
        }
        pthread_mutex_unlock(&lock);
    }

    return NULL;
}

int main(int argc, char *argv[])
{
    // Handle argv
    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s [IP_Address] [Port_Number]\n", argv[0]);
        exit(1);
    }
    const char *ip_address = argv[1];
    int port_number = atoi(argv[2]);

    // Connect server
    int client_socket = connect_server(ip_address, port_number);

    pthread_t thread_id;
    if (pthread_create(&thread_id, NULL, &server_response_handler, &client_socket))
    {
        perror("Could not create thread");
        return 1;
    }

    int choice = 0;

    while (choice != 4)
    {
        menu();
        while (isResponse != 1)
        {
            sleep(0.1);
        }
        printf("Enter your choice(1-4): ");
        input(&choice, "int");
        isResponse = 0;

        switch (choice)
        {
        case 0:
            signUp(client_socket);
            break;
        case 1:
            login(client_socket);
            break;
        case 2:
            getListUserOnline(client_socket);
            break;
        case 3:
            logout(client_socket);
            break;
        case 4:
            exit(1);
            break;
        case 5:
            request(client_socket);
            break;
        default:
            printf("Invalid choice. Please enter a valid option (1-4).\n");
            break;
        }
        choice = -1;
    }

    pthread_join(thread_id, NULL);
    close(client_socket);

    return 0;
}
