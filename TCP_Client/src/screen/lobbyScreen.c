#include "screens.h"
#include "../feature/Auth/auth.h"

void lobbyScreen(int client_socket)
{
    int menu;
    // system("clear");
    char buffer[STRING_LENGTH];
    do
    {   
        recv_with_error_handling(
            client_socket,
            buffer,
            sizeof(buffer),
            "Error receiving data from the client");
        printf("receive buffer : '%s'\n", buffer);
        printf(" =================== Caro =================== \n");
        printf(" Hello username ! Welcome back !\n");
        printf(" 1. Show Ranking. \n");
        printf(" 2. Chanllenge.\n");
        printf(" 3. Log out. \n");
        printf(" 0. Exit program. \n");
        printf(" ============================================ \n");
        printf(" Enter your choice: ");
        scanf("%d", &menu);
        system("clear");
        switch (menu)
        {
        case 1:
            rankingScreen(client_socket);
            break;
        case 2:
            challengeScreen(client_socket);
            break;
        case 3:
            logout(client_socket);
            loginScreen(client_socket);
            break;
        case 0:
            exit(0);
            break;
        default:
            break;
        }
    }while (strcmp(buffer, "RECEIVECHALLANGE")); 
    
}