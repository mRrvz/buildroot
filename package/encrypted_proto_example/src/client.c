#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define DEFAULT_PORT	8080
#define DEFAULT_MSG	"Hello from client"

#define BUF_SIZE	1024

#define IPPROTO_ENCRYPTED	144

int main(int argc, char *argv[])
{
	struct sockaddr_in server_addr;
	ssize_t bytes;
	int server_fd;
	int port = DEFAULT_PORT;
	char *client_msg = DEFAULT_MSG;
	char buffer[BUF_SIZE] = { 0 };
	socklen_t len = sizeof(server_addr);

	if (argc > 1)
		client_msg = argv[1];

	if (argc > 2)
		port = strtol(argv[2], NULL, 10);

	memset(&server_addr, 0, sizeof(server_addr));

	if ((server_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_ENCRYPTED)) < 0) {
		perror("Failed to create socket");
		exit(EXIT_FAILURE);
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");;
	server_addr.sin_port = htons(port);

	sendto(server_fd, client_msg, strlen(client_msg),
	       MSG_CONFIRM, (const struct sockaddr *) &server_addr, len);

	printf("Sent to server: %s\n", client_msg);

	bytes = recvfrom(server_fd, buffer, BUF_SIZE - 1,
			 MSG_WAITALL, (struct sockaddr *)&server_addr,
			 &len);
	buffer[bytes] = '\0';

	printf("Got from server: %s\n", buffer);

	close(server_fd);

	return 0;
}
