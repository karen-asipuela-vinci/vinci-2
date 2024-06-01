#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>

#include "utils_v1.h"

#define MESSAGE_SIZE 8192

/**
 * PRE: servierIP : a valid IP address
 *      serverPort: a valid port number
 * POST: on success, connects a client socket to serverIP:serverPort ;
 *       on failure, displays error cause and quits the program
 * RES: return socket file descriptor
 */
int initSocketClient(char serverIP[16], int serverPort)
{
	int sockfd = ssocket();
	sconnect(serverIP, serverPort, sockfd);
	return sockfd;
}

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		printf("%s\n", "Usage argv[0] ServerIP ServerPort");
		exit(1);
	}

	// initClient before read keyboard ... not a good idea
	int sockfd = initSocketClient(argv[1], atoi(argv[2]));

	printf("Bienvenue dans le programe vache - Entrez votre pseudo\n");

	char msg[MESSAGE_SIZE];
	sread(0, msg, 256);

	swrite(sockfd, msg, sizeof(msg));

	/* wait server response */
	sread(sockfd, msg, sizeof(msg));

	printf("Réponse du serveur : \n");
	printf("%s\n", msg);

	sclose(sockfd);

	return 0;
}
