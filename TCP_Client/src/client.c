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
#include "./feature/Challenge/challenge.h"

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

    int choice = 0;

    while (choice != 4)
    {
        menu();
        printf("Enter your choice(1-4): ");
        input(&choice, "int");

        switch (choice)
        {
        case 1:
            sign_up(client_socket);
            break;
        case 2:
            login(client_socket);
            break;
        case 3:
            getListUserOnline(client_socket);
            break;
        case 4:
            challenge(client_socket);
            break;
        case 5:
            get_challenged_list(client_socket);
            break;
        case 99:
            logout(client_socket);
            break;
        case 100:
            exit(1);
            break;
        default:
            printf("Invalid choice. Please enter a valid option (1-4).\n");
            break;
        }
        choice = -1;
    }

    close(client_socket);

    return 0;
}
