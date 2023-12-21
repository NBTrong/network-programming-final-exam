void readyScreen()
{
    int menu;
    system("clear");
    while (1)
    {
        system("clear");
        printf(" =================== Caro =================== \n");
        printf(" username is ready, waiting for match ...\n");
        printf(" 1. Back to lobby \n");
        printf(" 0. Exit program. \n");
        printf(" ============================================ \n");
        // printf(" Enter your choice: ");
        // printf(" Join game in 3s\n");
        // sleep(1);
        // printf(" Join game in 2s\n");
        // sleep(1);
        // printf(" Join game in 1s\n");
        // sleep(1);
        inGameScreen();
        scanf("%d", &menu);
        switch (menu)
        {
        case 1:
            lobbyScreen();
            break;
        case 0:
            exit(0);
        default:
            break;
        }
    }
}