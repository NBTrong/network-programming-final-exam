#include "utils.h"

void input(void *data, char *dataType)
{
    if (strcmp(dataType, "int") == 0)
    {
        scanf("%d", (int *)data);
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ; // Discard any remaining characters in the input buffer
    }
    else if (strcmp(dataType, "float") == 0)
    {
        scanf("%f", (float *)data);
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ; // Discard any remaining characters in the input buffer
    }
    else if (strcmp(dataType, "char") == 0)
    {
        scanf(" %c", (char *)data);
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ; // Discard any remaining characters in the input buffer
    }
    else if (strcmp(dataType, "string") == 0)
    {
        char buffer[100];
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strlen(buffer) - 1] = '\0'; // Remove the newline character
        strcpy((char *)data, buffer);
    }
};
