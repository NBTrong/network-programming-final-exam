#include "screens.h"
#include "../feature/Auth/auth.h"

void challengeScreen(int client_socket)
{
    // rankingScreen(client_socket);
    
    char chossenUser[STRING_LENGTH];
    char buffer[STRING_LENGTH];
    char message[STRING_LENGTH + 5];
    // sprintf(message, "GETONLINEUSER");
    // printf("\nsent message: '%s'\n", message);
    // send_with_error_handling(client_socket,buffer,message,"Send message login status error");

    // receive_online_session(client_socket);
    int chossenUserID;
    printf("Enter the user ID you want to challenge: ");
    scanf("%d", &chossenUserID);
    // system("clear");
    printf("Challenge sent to user %d\n", chossenUserID);
    snprintf(message, sizeof(message), "SENDCHALLANGE %d", chossenUserID);
    send_with_error_handling(
        client_socket,
        buffer,
        message,
        "Send message login status error");

    recv_with_error_handling(
        client_socket,
        buffer,
        sizeof(buffer),
        "Error receiving data from the client");
    printf("receive buffer : '%s'\n", buffer);
    printf("Waiting for response from user %d\n", chossenUserID);
    if (atoi(buffer) == 120)
    {
        printf("User %d accepted your challenge\n", chossenUserID);
        sleep(3);
        inGameScreen(client_socket);
    }
    else
    {
        printf("User %d rejected your challenge\n", chossenUserID);
    }
    {
        /* code */
    }
    
}