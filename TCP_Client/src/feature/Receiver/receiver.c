#include "receiver.h"

void file_receiving_protocol(int sender_socket)
{
    char request[STRING_LENGTH];
    char response[STRING_LENGTH];

    // Receive the filename and size from the client
    if (recv_with_error_handling(sender_socket, request, sizeof(request),
                                 "Error Receive filename and size failed") <= 0)
        return;

    // Get file name, file size
    char file_name[STRING_LENGTH];
    unsigned long long int file_size;
    sscanf(request, "UPLD %s %llu", file_name, &file_size);
    printf("File name: %s, file size: %llu\n", file_name, file_size);
    if (file_size > FILE_SIZE_LIMIT)
    {
        char message[STRING_LENGTH] = "";
        sprintf(message, "-ERR The file is too large, please make sure the file is smaller than %ld byte", FILE_SIZE_LIMIT);
        send_with_error_handling(
            sender_socket,
            response,
            message,
            "Error sending file request message");
        return;
    }

    // Ask client to send files
    send_with_error_handling(
        sender_socket,
        response,
        "+OK Please send file",
        "Error sending file request message");

    // Receive file
    srand(time(NULL));
    int random_number = rand() % 100 + 1;
    char file_path[1024 * 2];
    sprintf(file_path, "%s/socket_id_%d_%s", "TCP_Client/logs", random_number, file_name);
    FILE *file = fopen(file_path, "wb");
    if (file == NULL)
    {
        perror("Error opening file for writing");
        return;
    }

    unsigned long long int received = 0;
    printf("Receiving ...\n");
    char buffer[STRING_LENGTH];
    while (received < file_size)
    {
        int bytes_received = recv(sender_socket, buffer, sizeof(buffer), 0);
        if (bytes_received <= 0)
        {
            perror("Error receiving data from the client");
            return;
        }
        fwrite(buffer, 1, bytes_received, file);
        received += bytes_received;
    }

    fclose(file);
    send_with_error_handling(
        sender_socket,
        response,
        "+OK Successful upload",
        "Error sending success message");
}
