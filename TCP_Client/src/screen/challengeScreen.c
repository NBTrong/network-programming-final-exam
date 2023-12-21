void challengeScreen()
{
    rankingScreen();
    int chossenUser;
    printf("Enter the user ID you want to challenge: ");
    scanf("%d", &chossenUser);
    system("clear");
    printf("Challenge sent to user %d\n", chossenUser);
    printf("Waiting for response from user %d\n", chossenUser);
    // sleep(3);
    inGameScreen();
}