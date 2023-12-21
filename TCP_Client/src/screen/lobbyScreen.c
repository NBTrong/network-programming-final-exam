void lobbyScreen()
{
    int menu;
    system("clear");
    while (1)
    {
        printf(" =================== Caro =================== \n");
        printf(" Hello username ! Welcome back !\n");
        printf(" 1. Ready to game. \n");
        printf(" 2. Ranking. \n");
        printf(" 3. Chanllenge.\n");
        printf(" 4. Log out. \n");
        printf(" 0. Exit program. \n");
        printf(" ============================================ \n");
        printf(" Enter your choice: ");
        scanf("%d", &menu);
        system("clear");
        switch (menu)
        {
        case 1:
            readyScreen();
            break;
        case 2:
            rankingScreen();
            break;
        case 3:
            challengeScreen();
            break;
        case 4:
            loginScreen();
            break;
        case 0:
            exit(0);
        default:
            break;
        }
    }
}