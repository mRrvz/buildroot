#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define DEFAULT_PORT	8080
#define DEFAULT_MSG	"Hello from server"

#define BUF_SIZE	1024

#define IPPROTO_ENCRYPTED	144

int main(int argc, char *argv[])
{
	struct sockaddr_in server_addr, client_addr;
	ssize_t bytes;
	int server_fd;
	int port = DEFAULT_PORT;
	char *server_msg = DEFAULT_MSG;
	char buffer[BUF_SIZE] = { 0 };
	socklen_t len = sizeof(client_addr);

	if (argc > 1)
		server_msg = argv[1];

	if (argc > 2)
		port = strtol(argv[2], NULL, 10);

	memset(&server_addr, 0, sizeof(server_addr));
	memset(&client_addr, 0, sizeof(client_addr));

	if ((server_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_ENCRYPTED)) < 0) {
		perror("Failed to create socket");
		exit(EXIT_FAILURE);
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(port);

	if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	bytes = recvfrom(server_fd, buffer, BUF_SIZE - 1,
			 MSG_WAITALL, (struct sockaddr *)&client_addr,
			 &len);
	buffer[bytes] = '\0';

	printf("Got from client: %s\n", buffer);

	sendto(server_fd, server_msg, strlen(server_msg),
	       MSG_CONFIRM, (const struct sockaddr *) &client_addr, len);

	printf("Sent to client: %s\n", server_msg);

	close(server_fd);

	return 0;
}
