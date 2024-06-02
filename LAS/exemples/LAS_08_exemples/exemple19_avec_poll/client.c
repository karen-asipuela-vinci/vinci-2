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

// PRE: ServierIP : a valid IP address
//      ServerPort: a valid port number
// POST: on success connects a client socket to ServerIP:port
//       return socket file descriptor
//       on failure, displays error cause and quits the program
// Cette fonction initialise un socket client et le connecte à un serveur spécifié par son IP et son port.
// En cas de succès, elle renvoie le descripteur de fichier du socket.
// En cas d'échec, elle affiche la cause de l'erreur et quitte le programme.
int initSocketClient(char ServerIP[16], int Serverport)
{
	int sockfd = ssocket(); // crée un nouveau socket
	// socket = point de terminaison d'une communication bidirectionnelle entre 2 programmes sur un réseau
	// communication entre 2 sockets
	sconnect(ServerIP, Serverport, sockfd);
	return sockfd;
}

int main(int argc, char **argv)
{
	// vérifie que le nombre d'arguments est correct
	if (argc != 3)
	{
		printf("%s\n", "Usage argv[0] ServerIP ServerPort");
		exit(1);
	}

	// initialise le socket client et le connecte au serveur
	// serveur = atoi(argv[2])?
	int sockfd = initSocketClient(argv[1], atoi(argv[2]));

	printf("Bienvenue dans le programe vache - Entrez votre pseudo\n");

	char msg[MESSAGE_SIZE]; // crée un buffer pour stocker les messages

	// lit le message de l'utilisateur à partir de l'entrée standard (clavier)
	sread(0, msg, 256);

	// envoie le message au serveur
	swrite(sockfd, msg, sizeof(msg));

	// attend une réponse du serveur
	sread(sockfd, msg, sizeof(msg));

	// affiche la réponse du serveur
	printf("Réponse du serveur : \n");
	printf("%s\n", msg);

	// !fermer le socket client
	sclose(sockfd);

	return 0;
}
