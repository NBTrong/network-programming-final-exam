#include "tcp.h"

char *int_to_string(int num)
{
    char *str = (char *)malloc(20);
    sprintf(str, "%d", num);
    return str;
}

int send_with_error_handling(const int server_socket, char *buffer, const char *message, const char *error_message)
{
    size_t message_length = strlen(message);

    sprintf(buffer, "%4zu", message_length);

    strcpy(buffer + 4, message);

    if (send(server_socket, buffer, message_length + 4, 0) < 0)
    {
        perror(error_message);
        memset(buffer, 0, message_length + 4);
        return 0;
    }

    printf("Send to client %d: %s\n", server_socket, message);
    return 1;
}

int recv_with_error_handling(const int client_socket, char *buffer, size_t size, const char *error_message)
{
    // Receive the 4-character length prefix
    char length_buffer[5]; // 4 characters for length + 1 for null terminator
    memset(length_buffer, 0, sizeof(length_buffer));

    int result = recv(client_socket, length_buffer, 4, MSG_WAITALL);
    if (result < 0)
    {
        perror(error_message);
        return result;
    }
    else if (result == 0)
    {
        printf("Client %d disconnect\n", client_socket);
        close(client_socket);
        return result;
    }

    // Convert the length_buffer to a long using strtol
    char *endptr;
    long content_length = strtol(length_buffer, &endptr, 10);

    // Check for conversion errors
    if (*endptr != '\0' || content_length <= 0 || content_length > (long int)size)
    {
        fprintf(stderr, "Invalid message length. Disconnecting client %d.\n", client_socket);
        close(client_socket);
        return 0;
    }

    // Receive the actual content based on the calculated length
    result = recv(client_socket, buffer, content_length, 0);
    if (result < 0)
    {
        perror(error_message);
    }
    else if (result == 0)
    {
        printf("Client %d disconnect\n", client_socket);
        close(client_socket);
    }

    // Null-terminate the received content
    buffer[content_length] = '\0';

    return result;
}

int init_server(int port_number)
{
    int server_socket;
    struct sockaddr_in server_addr;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0)
    {
        perror("Error creating socket");
        exit(1);
    }

    memset((char *)&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port_number);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Error binding");
        exit(1);
    }

    listen(server_socket, 5);

    printf("Server is listening on port %d\n", port_number);

    return server_socket;
}
