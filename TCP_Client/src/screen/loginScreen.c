#include "screens.h"
#include "../feature/Auth/auth.h"
void loginScreen(int client_socket)
{
    int menu;
    while (1)
    {
        printf(" =================== Caro =================== \n");
        printf(" 1. Login. \n");
        printf(" 2. Register. \n");
        printf(" 0. Exit program. \n");
        printf(" ============================================ \n");
        printf(" Enter your choice: ");
        scanf("%d", &menu);
        // system("clear");
        switch (menu)
        {
        case 1:
            if ( login(client_socket) == 110)
                lobbyScreen(client_socket);
            // inGameScreen(client_socket);
            break;
        case 2:
            break;
        case 0:
            exit(0);
            break;
        default:
            break;
        }
    }
}
