#define MAX_LEN 255

void registerScreen()
{
    int menu;
    char username[MAX_LEN], password[MAX_LEN];
    while (1)
    {
        printf(" =================== Caro =================== \n");
        printf(" 1. Enter your username:");
        scanf("%s", username);
        // printf (" 2. Enter your password:");
        printf(" Enter your choice: ");
        scanf("%d", &menu);
        system("clear");
        switch (menu)
        {
        case 1:
            lobbyScreen();
            break;
        case 2:
            break;
        case 0:
            exit(0);
        default:
            break;
        }
    }
}
