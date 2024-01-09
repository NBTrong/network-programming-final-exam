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
        printf("Server disconnect\n");
        close(client_socket);
        return result;
    }

    // Convert the length_buffer to a long using strtol
    char *endptr;
    long content_length = strtol(length_buffer, &endptr, 10);

    // Check for conversion errors
    if (*endptr != '\0' || content_length <= 0 || content_length > (long int)size)
    {
        fprintf(stderr, "Invalid message length. Disconnecting Server.\n");
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
        printf("Server %d disconnect\n", client_socket);
        close(client_socket);
    }

    // Null-terminate the received content
    buffer[content_length] = '\0';

    printf("Recv from server: %s\n", buffer);

    return result;
}

int connect_server(const char *server_ip_address, int server_port_number)
{
    int client_socket;
    struct sockaddr_in server_addr;

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0)
    {
        perror("Error creating socket");
        exit(1);
    }

    memset((char *)&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(server_ip_address);
    server_addr.sin_port = htons(server_port_number);

    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Error connecting to the server");
        exit(1);
    }

    char buffer[1024];
    recv_with_error_handling(
        client_socket,
        buffer,
        sizeof(buffer),
        "Error receiving data from the client");
    printStatusMessage(buffer);

    return client_socket;
}

void printStatusMessage(const char *status)
{
    int code = atoi(status);

    switch (code)
    {
    case 100:
        printf("Connection to the service successful.\n");
        break;
    case 110:
        printf("Login successfully.\n");
        break;
    case 211:
        printf("Login failed: Account is locked.\n");
        break;
    case 212:
        printf("Login failed: Account does not exist.\n");
        break;
    case 213:
        printf("Login failed: Account is already logged in on another client.\n");
        break;
    case 214:
        printf("Login failed: You are already logged in.\n");
        break;
    case 300:
        printf("Login failed: Undefined message request type.\n");
        break;
    case 120:
        printf("Post article successful.\n");
        break;
    case 221:
        printf("Cannot use the service, you are not logged in.\n");
        break;
    case 130:
        printf("Logout successful.\n");
        break;
    case 410:
        printf("Account exited, please other username\n");
        break;
    case 411:
        printf("Sign up successfully, please login to use services\n");
        break;
    case 511:
        printf("Get list user successfully\n");
        break;
    default:
        printf("Unknown status code: %d\n", code);
        break;
    }
};
