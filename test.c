#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_MESSAGE_SIZE 1024

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Sử dụng: %s <ip_server> <port_server>\n", argv[0]);
        return 1;
    }

    const char *ip_server = argv[1];
    int port_server = atoi(argv[2]);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        error("Không thể tạo socket");
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port_server);
    if (inet_pton(AF_INET, ip_server, &(server_addr.sin_addr)) <= 0)
    {
        error("inet_pton() lỗi");
    }

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        error("Không thể kết nối đến server");
    }

    FILE *file = fopen("test-1-user-function.txt", "r");
    if (file == NULL)
    {
        error("Không thể mở file test-1-user-function.txt");
    }

    char message[MAX_MESSAGE_SIZE];
    char received_message[MAX_MESSAGE_SIZE];
    char next_message[MAX_MESSAGE_SIZE];

    memset(received_message, 0, sizeof(received_message));

    // Nhận tin nhắn từ server
    recv(sockfd, received_message, sizeof(received_message), 0);
    printf("       Nhận: [%s]\n", received_message);
    // Đối chiếu với dòng dầu tiên trong file
    fgets(next_message, sizeof(next_message), file);
    next_message[strcspn(next_message, "\n")] = '\0';
    printf("So sánh với: [%s]\n", next_message);
    if (strncmp(received_message, next_message, strlen(received_message)) != 0)
    {
        printf("Lỗi: Tin nhắn không khớp với dòng tiếp theo\n");
        // break;
    }
    else
    {
        printf("=> Trả về đúng định dạng\n");
    }
    printf("\n\n");
    memset(received_message, 0, sizeof(received_message));

    while (fgets(message, sizeof(message), file) != NULL)
    {

        message[strcspn(message, "\n")] = '\0';
        send(sockfd, message, strlen(message), 0);
        printf("       Gửi : [%s]\n", message);

        // Nhận tin nhắn từ server
        recv(sockfd, received_message, sizeof(received_message), 0);
        printf("       Nhận: [%s] \n", received_message);

        // if (strncmp(received_message, "ERROR", strlen("ERROR")) == 0) {
        //     printf("Lỗi: %s\n", received_message);
        //     break;
        // }

        // Đối chiếu với dòng tiếp theo trong file
        if (fgets(next_message, sizeof(next_message), file) != NULL)
        {

            next_message[strcspn(next_message, "\n")] = '\0';
            printf("So sánh với: [%s]\n", next_message);
            if (strncmp(received_message, next_message, strlen(received_message)) != 0)
            {
                printf("Lỗi: Tin nhắn không khớp với dòng tiếp theo\n");
                // break;
            }
            else
            {
                printf("=> Trả về đúng định dạng\n");
            }
        }
        printf("\n\n");
        memset(message, 0, sizeof(message));
        memset(received_message, 0, sizeof(received_message));
    }

    fclose(file);
    close(sockfd);

    return 0;
}
