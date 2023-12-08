#include <stdio.h>

#include <stdlib.h>

#include <sys/types.h>

#include <sys/socket.h>

#include <netinet/in.h>

#include <arpa/inet.h>

#include <string.h>

#include <unistd.h>

#include <pthread.h>

#include <libgen.h>

/**

 * Connect to a server using the specified IP address and port number.

 * @param server_ip_address The IP address of the server to connect to.

 * @param server_port_number The port number on the server to establish the connection.

 * @return A socket descriptor representing the connection to the server, or -1 in case of an error.

 */

int connect_server(const char *server_ip_address, int server_port_number);

/**

 * Send a message on the specified server socket with error handling.

 * @param server_socket The socket descriptor for the server connection.

 * @param buffer The buffer containing the message to send.

 * @param message The message to be sent on the server socket.

 * @param error_message The error message to display in case of sending failure.

 * @return 0 on success, or -1 in case of an error.

 */

int send_with_error_handling(const int server_socket, char *buffer, const char *message, const char *error_message);

/**

 * Receive a message on the specified client socket with error handling.

 * @param client_socket The socket descriptor for the client connection.

 * @param buffer The buffer to store the received message.

 * @param size The size of the buffer.

 * @param error_message The error message to display in case of receiving failure.

 * @return The number of bytes received on success, or -1 in case of an error.

 */

int recv_with_error_handling(const int client_socket, char *buffer, size_t size, const char *error_message);

void printStatusMessage(const char *status);

#define MAX_NTHREADS 16

#define MAX_NREQUEST 10

#define MAX_NCONNS 1024

#define MAX_NCONNS_PER_THREAD 16

#define SERVER_IP "127.0.0.1"

#define BUFF_SIZE 2048

#define SUCCESS_LOGIN "110"

#define SUCCESS_POST "120"

#define SUCCESS_LOGOUT "130"

void *worker1(void *);

void *worker2(void *);

void *worker3(void *);

int serverPort;

struct sockaddr_in serverAddr;

int main(int argc, char **argv)

{

	int nthreads = 0;

	if (argc != 3)
	{

		printf("usage: test <#serverPort> <#threads>\n");

		return 0;
	}

	serverPort = atoi(argv[1]);

	int client;

	char sBuff[BUFF_SIZE], rBuff[BUFF_SIZE];

	int ret;

	// Define the address of the server

	bzero(&serverAddr, sizeof(serverAddr));

	serverAddr.sin_family = AF_INET;

	serverAddr.sin_port = htons(serverPort);

	serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

	if ((client = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{

		perror("\nsocket() Error: ");

		exit(EXIT_FAILURE);
	}

	struct timeval tv;

	tv.tv_sec = 0;

	tv.tv_usec = 100000; // Time-out interval: 100000ms

	if (setsockopt(client, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(struct timeval)) == -1)
	{

		perror("\nsetsockopt() Error: ");

		exit(EXIT_FAILURE);
	}

	if (connect(client, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr)) == -1)
	{

		perror("\nconnect() Error: ");

		exit(EXIT_FAILURE);
	}

	// Connection test

	ret = recv(client, rBuff, BUFF_SIZE, 0);

	if (ret <= 0)

		printf("Connect test fail!\n");

	else
	{

		rBuff[ret] = 0;

		printf("%s\n", rBuff);
	}

	// Sequence test

	strcpy(sBuff, "POST Hello");

	send_with_error_handling(client, rBuff, sBuff, "Send message login status error");

	recv_with_error_handling(client, rBuff, BUFF_SIZE, "Error receiving data from the client");

	printStatusMessage(rBuff);

	if (ret <= 0)

		printf("Sequence test fail!\n");

	else
	{

		rBuff[ret] = 0;

		printf("Main: %s-->%s\n", sBuff, rBuff);

		if (strstr(rBuff, SUCCESS_POST) != 0)

			printf("Sequence test fail!\n");
	}

	strcpy(sBuff, "BYE");

	send_with_error_handling(client, rBuff, sBuff, "Send message login status error");

	recv_with_error_handling(client, rBuff, BUFF_SIZE, "Error receiving data from the client");

	printStatusMessage(rBuff);

	if (ret <= 0)

		printf("Sequence test fail!\n");

	else
	{

		rBuff[ret] = 0;

		printf("Main: %s-->%s\n", sBuff, rBuff);

		if (strstr(rBuff, SUCCESS_LOGOUT) != 0)

			printf("Sequence test fail!\n");
	}

	// Function test

	strcpy(sBuff, "USER ductq");

	send_with_error_handling(client, rBuff, sBuff, "Send message login status error");

	recv_with_error_handling(client, rBuff, BUFF_SIZE, "Error receiving data from the client");

	printStatusMessage(rBuff);

	if (ret > 0)
	{

		rBuff[ret] = 0;

		printf("Main: %s-->%s\n\n", sBuff, rBuff);

		if (strstr(rBuff, SUCCESS_LOGIN) != 0)

			printf("Login test fail!\n");
	}

	else

		printf("Login test fail!\n");

	strcpy(sBuff, "USER admin");

	send_with_error_handling(client, rBuff, sBuff, "Send message login status error");

	recv_with_error_handling(client, rBuff, BUFF_SIZE, "Error receiving data from the client");

	printStatusMessage(rBuff);

	if (ret > 0)
	{

		rBuff[ret] = 0;

		printf("Main: %s-->%s\n", sBuff, rBuff);

		if (strstr(rBuff, SUCCESS_LOGIN) == 0)

			printf("Login test fail!\n");
	}

	else

		printf("Login test fail!\n");

	strcpy(sBuff, "USER tungbt");

	send_with_error_handling(client, rBuff, sBuff, "Send message login status error");

	recv_with_error_handling(client, rBuff, BUFF_SIZE, "Error receiving data from the client");

	printStatusMessage(rBuff);

	if (ret > 0)
	{

		rBuff[ret] = 0;

		printf("Main: %s-->%s\n", sBuff, rBuff);

		if (strstr(rBuff, SUCCESS_LOGIN) != 0)

			printf("Login test fail!\n");
	}

	else

		printf("Login test fail!\n");

	strcpy(sBuff, "POST Hello");

	send_with_error_handling(client, rBuff, sBuff, "Send message login status error");

	recv_with_error_handling(client, rBuff, BUFF_SIZE, "Error receiving data from the client");

	printStatusMessage(rBuff);

	if (ret > 0)
	{

		rBuff[ret] = 0;

		printf("Main: %s-->%s\n", sBuff, rBuff);

		if (strstr(rBuff, SUCCESS_POST) == 0)

			printf("Post message test fail!\n");
	}

	else

		printf("Post message test fail!\n");

	strcpy(sBuff, "BYE");

	send_with_error_handling(client, rBuff, sBuff, "Send message login status error");

	recv_with_error_handling(client, rBuff, BUFF_SIZE, "Error receiving data from the client");

	printStatusMessage(rBuff);

	if (ret > 0)
	{

		rBuff[ret] = 0;

		printf("Main: %s-->%s\n", sBuff, rBuff);

		if (strstr(rBuff, SUCCESS_LOGOUT) == 0)

			printf("Logout test fail!\n");
	}

	else

		printf("Logout test fail!\n");

	strcpy(sBuff, "POST Hello");

	send_with_error_handling(client, rBuff, sBuff, "Send message login status error");

	recv_with_error_handling(client, rBuff, BUFF_SIZE, "Error receiving data from the client");

	printStatusMessage(rBuff);

	if (ret <= 0)

		printf("Sequence test fail!\n");

	else
	{

		rBuff[ret] = 0;

		printf("Main: %s-->%s\n", sBuff, rBuff);

		if (strstr(rBuff, SUCCESS_POST) != 0)

			printf("Sequence test fail!\n");
	}

	strcpy(sBuff, "USER tungbt");

	send_with_error_handling(client, rBuff, sBuff, "Send message login status error");

	recv_with_error_handling(client, rBuff, BUFF_SIZE, "Error receiving data from the client");

	printStatusMessage(rBuff);

	if (ret > 0)
	{

		rBuff[ret] = 0;

		printf("Main: %s-->%s\n", sBuff, rBuff);

		if (strstr(rBuff, SUCCESS_LOGIN) == 0)

			printf("Login test fail!\n");
	}

	else

		printf("Login test fail!\n");

	strcpy(sBuff, "BYE");

	send_with_error_handling(client, rBuff, sBuff, "Send message login status error");

	recv_with_error_handling(client, rBuff, BUFF_SIZE, "Error receiving data from the client");

	printStatusMessage(rBuff);

	if (ret > 0)
	{

		rBuff[ret] = 0;

		printf("Main: %s-->%s\n", sBuff, rBuff);

		if (strstr(rBuff, SUCCESS_LOGOUT) == 0)

			printf("Logout test fail!\n");
	}

	else

		printf("Logout test fail!\n");

	strcpy(sBuff, "USER ");

	send_with_error_handling(client, rBuff, sBuff, "Send message login status error");

	recv_with_error_handling(client, rBuff, BUFF_SIZE, "Error receiving data from the client");

	printStatusMessage(rBuff);

	if (ret <= 0)

		printf("Syntax test fail!\n");

	else
	{

		rBuff[ret] = 0;

		printf("Main: %s-->%s\n", sBuff, rBuff);

		if (strstr(rBuff, "300") != 0)

			printf("Syntax test fail!\n");
	}

	strcpy(sBuff, "foo");

	send_with_error_handling(client, rBuff, sBuff, "Send message login status error");

	recv_with_error_handling(client, rBuff, BUFF_SIZE, "Error receiving data from the client");

	printStatusMessage(rBuff);

	if (ret <= 0)

		printf("Syntax test fail!\n");

	else
	{

		rBuff[ret] = 0;

		printf("Main: %s-->%s\n", sBuff, rBuff);
	}

	pthread_t tid_worker1, tid_worker2, tid_worker3[MAX_NTHREADS];

	int any;

	printf("Press any number!\n");

	scanf("%d", &any);

	// Concurency test 1

	pthread_create(&tid_worker1, NULL, worker1, NULL);

	pthread_create(&tid_worker2, NULL, worker2, NULL);

	pthread_join(tid_worker1, NULL);

	pthread_join(tid_worker2, NULL);

	// Concurency test 2

	int numConn = 0;

	struct timespec ts;

	ts.tv_sec = 0;

	ts.tv_nsec = 10000000;

	printf("Number of concurent connections: ");

	scanf("%d", &numConn);

	if (numConn > 0)
	{

		char buff[BUFF_SIZE];

		int numSession = 0, numConnected = 0;

		int clients[MAX_NCONNS];

		if (numConn > MAX_NCONNS)
			numConn = MAX_NCONNS;

		for (int i = 0; i < numConn; i++)
		{

			clients[i] = socket(AF_INET, SOCK_STREAM, 0);

			if (connect(clients[i], (struct sockaddr *)&serverAddr, sizeof(serverAddr)))
			{

				perror("\nsocket() Error: ");

				break;
			}

			nanosleep(&ts, &ts);

			numConnected++;

			struct timeval tv2;

			tv2.tv_sec = 0;

			tv2.tv_usec = 100000; // Time-out interval: 100000ms

			setsockopt(clients[i], SOL_SOCKET, SO_RCVTIMEO, (const char *)(&tv2), sizeof(struct timeval));

			ret = recv(clients[i], rBuff, BUFF_SIZE, 0);

			if (ret <= 0)

				printf("Connect test fail!\n");

			else
			{

				rBuff[ret] = 0;

				printf("%s\n", rBuff);
			}

			strcpy(sBuff, "USER admin");

			send_with_error_handling(clients[i], rBuff, sBuff, "Send message login status error");

			recv_with_error_handling(clients[i], rBuff, BUFF_SIZE, "Error receiving data from the client");

			printStatusMessage(rBuff);

			if (ret <= 0)

				printf("recv() fail.\n");

			else
			{

				rBuff[ret] = 0;

				printf("Concurent test: %s\n", rBuff);

				numSession++;
			}
		}

		printf("\nNumber of success connection: %d", numConnected);

		printf("\nNumber of success session: %d\n", numSession);

		for (int i = 0; i < numConn; i++)

			close(clients[i]);
	}

	printf("Press any number!\n");

	scanf("%d", &any);

	// Concurency test 3

	nthreads = atoi(argv[2]);

	if (nthreads > MAX_NTHREADS)

		nthreads = MAX_NTHREADS;

	printf("Number of thread: %d\n", nthreads);

	/* create all workers */

	for (int i = 0; i < nthreads; i++)

		pthread_create(&tid_worker3[i], NULL, worker3, NULL);

	/* wait for all worker */

	for (int i = 0; i < nthreads; i++)

		pthread_join(tid_worker3[i], NULL);

	return 0;
}

void *worker1(void *arg)
{

	int client;

	char sBuff[BUFF_SIZE], rBuff[BUFF_SIZE];

	int ret;

	if ((client = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{

		perror("\nsocket() Error: ");

		exit(EXIT_FAILURE);
	}

	struct timeval tv;

	tv.tv_sec = 0;

	tv.tv_usec = 100000; // Time-out interval: 100000ms

	if (setsockopt(client, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(struct timeval)) == -1)
	{

		perror("\nsetsockopt() Error: ");

		exit(EXIT_FAILURE);
	}

	if (connect(client, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr)) == -1)
	{

		perror("\nconnect() Error: ");

		exit(EXIT_FAILURE);
	}

	// Connection test

	ret = recv(client, rBuff, BUFF_SIZE, 0);

	if (ret <= 0)

		printf("Connect test fail!\n");

	else
	{

		rBuff[ret] = 0;

		printf("Thread 1: %s\n", rBuff);
	}

	strcpy(sBuff, "USER tungbt");

	send_with_error_handling(client, rBuff, sBuff, "Send message login status error");

	ret = recv_with_error_handling(client, rBuff, BUFF_SIZE, "Error receiving data from the client");

	printStatusMessage(rBuff);

	if (ret > 0)
	{

		rBuff[ret] = 0;

		printf("Thread 1:  %s-->%s\n", sBuff, rBuff);
	}

	else

		printf("Receive on thread 1 failed\n");

	struct timespec ts;

	ts.tv_sec = 0;

	ts.tv_nsec = 10000000;

	for (int i = 0; i < 5; i++)
	{

		nanosleep(&ts, &ts);

		strcpy(sBuff, "POST Hello. I am tungbt");

		send_with_error_handling(client, rBuff, sBuff, "Send message login status error");

		ret = recv_with_error_handling(client, rBuff, BUFF_SIZE, "Error receiving data from the client");

		printStatusMessage(rBuff);

		if (ret > 0)
		{

			rBuff[ret] = 0;

			printf("Thread 1:  %s-->%s\n", sBuff, rBuff);
		}

		else

			printf("Receive on thread 1 failed\n");
	}

	strcpy(sBuff, "BYE");

	send_with_error_handling(client, rBuff, sBuff, "Send message login status error");

	ret = recv_with_error_handling(client, rBuff, BUFF_SIZE, "Error receiving data from the client");

	printStatusMessage(rBuff);

	if (ret > 0)
	{

		rBuff[ret] = 0;

		printf("Thread 1:  %s-->%s\n", sBuff, rBuff);
	}

	else

		printf("Receive on thread 1 failed\n");

	strcpy(sBuff, "USER test");

	send_with_error_handling(client, rBuff, sBuff, "Send message login status error");

	ret = recv_with_error_handling(client, rBuff, BUFF_SIZE, "Error receiving data from the client");

	printStatusMessage(rBuff);

	if (ret > 0)
	{

		rBuff[ret] = 0;

		printf("Thread 1:  %s-->%s\n", sBuff, rBuff);
	}

	else

		printf("Receive on thread 1 failed\n");

	for (int i = 0; i < 5; i++)
	{

		nanosleep(&ts, &ts);

		strcpy(sBuff, "POST Hello. I am test");

		send_with_error_handling(client, rBuff, sBuff, "Send message login status error");

		ret = recv_with_error_handling(client, rBuff, BUFF_SIZE, "Error receiving data from the client");

		printStatusMessage(rBuff);

		if (ret > 0)
		{

			rBuff[ret] = 0;

			printf("Thread 1:  %s-->%s\n", sBuff, rBuff);
		}

		else

			printf("Receive on thread 1 failed\n");
	}

	// Step 6: Close socket

	close(client);

	printf("Thread 1 end.\n");
}

void *worker2(void *arg)
{

	int client;

	char sBuff[BUFF_SIZE], rBuff[BUFF_SIZE];

	int ret;

	struct timespec ts;

	ts.tv_sec = 0;

	ts.tv_nsec = 1000000;

	nanosleep(&ts, &ts);

	if ((client = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{

		perror("\nsocket() Error: ");

		exit(EXIT_FAILURE);
	}

	struct timeval tv;

	tv.tv_sec = 0;

	tv.tv_usec = 100000; // Time-out interval: 100000ms

	if (setsockopt(client, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(struct timeval)) == -1)
	{

		perror("\nsetsockopt() Error: ");

		exit(EXIT_FAILURE);
	}

	if (connect(client, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr)) == -1)
	{

		perror("\nconnect() Error: ");

		exit(EXIT_FAILURE);
	}

	// Connection test

	ret = recv(client, rBuff, BUFF_SIZE, 0);

	if (ret <= 0)

		printf("Connect test fail!\n");

	else
	{

		rBuff[ret] = 0;

		printf("Thread 2: %s\n", rBuff);
	}

	strcpy(sBuff, "USER admin");

	send_with_error_handling(client, rBuff, sBuff, "Send message login status error");

	ret = recv_with_error_handling(client, rBuff, BUFF_SIZE, "Error receiving data from the client");

	printStatusMessage(rBuff);

	if (ret > 0)
	{

		rBuff[ret] = 0;

		printf("Thread 2:  %s-->%s\n", sBuff, rBuff);
	}

	else

		printf("Receive on thread failed\n");

	for (int i = 0; i < 10; i++)
	{

		nanosleep(&ts, &ts);

		strcpy(sBuff, "POST Hello. I am admin");

		send_with_error_handling(client, rBuff, sBuff, "Send message login status error");

		ret = recv_with_error_handling(client, rBuff, BUFF_SIZE, "Error receiving data from the client");

		printStatusMessage(rBuff);

		if (ret > 0)
		{

			rBuff[ret] = 0;

			printf("Thread 2:  %s-->%s\n", sBuff, rBuff);
		}

		else

			printf("Receive on thread failed\n");
	}

	strcpy(sBuff, "BYE");

	send_with_error_handling(client, rBuff, sBuff, "Send message login status error");

	ret = recv_with_error_handling(client, rBuff, BUFF_SIZE, "Error receiving data from the client");

	printStatusMessage(rBuff);

	if (ret > 0)
	{

		rBuff[ret] = 0;

		printf("Thread 2:  %s-->%s\n", sBuff, rBuff);
	}

	else

		printf("Receive on thread failed\n");

	strcpy(sBuff, "USER ductq");

	send_with_error_handling(client, rBuff, sBuff, "Send message login status error");

	ret = recv_with_error_handling(client, rBuff, BUFF_SIZE, "Error receiving data from the client");

	printStatusMessage(rBuff);

	if (ret > 0)
	{

		rBuff[ret] = 0;

		printf("Thread 2:  %s-->%s\n", sBuff, rBuff);
	}

	else

		printf("Receive on thread failed\n");

	// Step 6: Close socket

	close(client);

	printf("Thread 2 end.\n");
}

void *worker3(void *arg)

{

	int ret = 0;

	int numSession = 0, numConnected = 0;

	int clients[MAX_NCONNS];

	struct timespec ts;

	ts.tv_sec = 0;

	ts.tv_nsec = 20000000;

	char sBuff[BUFF_SIZE], rBuff[BUFF_SIZE + 1];

	for (int i = 0; i < MAX_NCONNS_PER_THREAD; i++)
	{

		clients[i] = socket(AF_INET, SOCK_STREAM, 0);

		if (connect(clients[i], (struct sockaddr *)&serverAddr, sizeof(serverAddr)))
		{

			perror("\nconnect() Error: ");

			break;
		}

		numConnected++;

		nanosleep(&ts, &ts);

		struct timeval tv2;

		tv2.tv_sec = 0;

		tv2.tv_usec = 100000; // Time-out interval: 100000ms

		if (setsockopt(clients[i], SOL_SOCKET, SO_RCVTIMEO, &tv2, sizeof(struct timeval)) == -1)
		{

			perror("\nsetsockopt() Error: ");

			exit(EXIT_FAILURE);
		}

		ret = recv(clients[i], rBuff, BUFF_SIZE, 0);

		if (ret <= 0)

			printf("Connect test fail!\n");

		else
		{

			rBuff[ret] = 0;

			printf("Worker 3: %s\n", rBuff);
		}

		strcpy(sBuff, "USER admin");

		send_with_error_handling(clients[i], rBuff, sBuff, "Send message login status error");

		ret = recv_with_error_handling(clients[i], rBuff, BUFF_SIZE, "Error receiving data from the client");

		printStatusMessage(rBuff);

		if (ret <= 0)

			printf("recv() fail.\n");

		else
		{

			rBuff[ret] = 0;

			printf("Worker 3: %s\n", rBuff);

			numSession++;
		}
	}

	printf("\nNumber of success connection: %d", numConnected);

	printf("\nNumber of success session: %d\n", numSession);

	for (int i = 0; i < MAX_NCONNS_PER_THREAD; i++)
	{

		int ok = 0;

		for (int k = 0; k < MAX_NREQUEST; k++)
		{

			strcpy(sBuff, "POST Hello. I am admin");

			send_with_error_handling(clients[i], rBuff, sBuff, "Send message login status error");

			ret = recv_with_error_handling(clients[i], rBuff, BUFF_SIZE, "Error receiving data from the client");

			printStatusMessage(rBuff);

			if (ret <= 0)

				printf("recv() %d fail.\n", k);

			else
			{

				ok++;
			}
		}

		if (ok < MAX_NREQUEST)
			printf("Concurency test 3 failed\n");
	}

	for (int i = 0; i < MAX_NCONNS_PER_THREAD; i++)

		close(clients[i]);
}

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

	default:

		printf("Unknown status code: %d\n", code);

		break;
	}
};