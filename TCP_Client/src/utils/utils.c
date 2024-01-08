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

char *processDataFromResponse(const char *response)
{
    // Check if the response starts with "SUCCESS"
    if (strncmp(response, "SUCCESS", 7) == 0)
    {
        // If successful, find the position of the first space after "SUCCESS"
        const char *firstSpace = strchr(response, ' ');

        if (firstSpace != NULL)
        {
            // Get the data part after "SUCCESS"
            const char *dataStart = firstSpace + 1;

            // Calculate the length of the data string
            size_t dataLength = strlen(dataStart);

            // Allocate memory for the data string and copy the data into it
            char *data = (char *)malloc(dataLength + 1);
            strncpy(data, dataStart, dataLength);
            data[dataLength] = '\0'; // Ensure the string is null-terminated

            return data;
        }
        else
        {
            return "";
        }
    }
    else if (strncmp(response, "ERROR", 5) == 0)
    {
        // If it's an error, print the error message and return NULL
        printf("Error: %s\n", response + 6); // Print the error message after "ERROR"
        return NULL;
    }
    else
    {
        // If neither SUCCESS nor ERROR, consider the response invalid
        printf("Error: Invalid response format\n");
        return NULL;
    }
}
