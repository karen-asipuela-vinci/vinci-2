#include <stdio.h>
#include "utils_v1.h"


int initSocketClient(char *serverIP, int serverPort)
{
	int sockfd = ssocket();
	sconnect(serverIP, serverPort, sockfd);
	return sockfd;
}

void sendMessageAndReceiveResponse(int sockfd, StructMessage *msg) {
    swrite(sockfd, msg, sizeof(*msg));
    sread(sockfd, msg, sizeof(*msg));
}

void disconnect_players(Player *tabPlayers, int nbPlayers)
{
	for (int i = 0; i < nbPlayers; i++)
		sclose(tabPlayers[i].sockfd);
	return;
}

int initSocketServer(int port)
{
	int sockfd = ssocket();

	int option = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(int));

	sbind(port, sockfd);

	slisten(sockfd, BACKLOG);

	return sockfd;
}