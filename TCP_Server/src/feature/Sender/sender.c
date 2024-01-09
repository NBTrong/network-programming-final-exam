#include "./sender.h"

char *handle_message(const char *buffer)
{
    char status[10];
    char message[1024];
    if (sscanf(buffer, "%9s %[^\n]", status, message) == 2)
    {
        if (strcmp(status, "+OK") == 0 || strcmp(status, "-ERR") == 0)
        {
            printf("Server: \"%s\", \"%s\"\n", status, message);
        }
        else
        {
            printf("Server: Invalid status.\n");
        }
    }
    else
    {
        printf("Server: Invalid format.\n");
    }
    return strdup(status);
}

void file_sending_protocol(int client_socket, char *file_path)
{
    // Open file
    FILE *file = fopen(file_path, "rb");
    if (file == NULL)
    {
        fprintf(stderr, "Error: Cannot open file '%s'\n", file_path);
        return;
    }

    // Get file size
    fseek(file, 0, SEEK_END);
    unsigned long long int file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Send file information
    char mess[1024];
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    char *file_name = basename(file_path);
    sprintf(buffer, "UPLD %s %llu", file_name, file_size);
    send_with_error_handling(
        client_socket,
        mess,
        buffer,
        "Error sending file request message");

    // Receive request send file from server
    memset(buffer, 0, strlen(buffer));
    recv_with_error_handling(client_socket,
                             buffer,
                             sizeof(buffer),
                             "Error receiving file request message from the server");
    char *status = handle_message(buffer);
    if (strcmp(status, "-ERR") == 0)
        return;

    // Send file to server
    printf("Sending ...\n");
    while (!feof(file))
    {
        memset(buffer, 0, sizeof(buffer));
        int bytes_read = fread(buffer, 1, sizeof(buffer), file);
        if (send(client_socket, buffer, bytes_read, 0) < 0)
        {
            perror("Error sending the file to the server");
            break;
        }
    }

    // Receive result
    memset(buffer, 0, sizeof(buffer));
    recv_with_error_handling(client_socket,
                             buffer,
                             sizeof(buffer),
                             "Error receiving file request message from the server");
    handle_message(buffer);
    fclose(file);
}