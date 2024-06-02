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

// ! SANS POLL
/**
 * PRE: servierIP : une adresse IP valide
 *      serverPort: un numéro de port valide
 * POST: en cas de succès, connecte un socket client à serverIP:serverPort ;
 *       en cas d'échec, affiche la cause de l'erreur et quitte le programme
 * RES: retourne le descripteur de fichier de socket
 */
int initSocketClient(char serverIP[16], int serverPort)
{
	// Crée un nouveau socket et retourne son descripteur de fichier
	int sockfd = ssocket();
	// Connecte le socket au serveur spécifié par serverIP et serverPort
	sconnect(serverIP, serverPort, sockfd);
	return sockfd;
}

int main(int argc, char **argv)
{
	// Vérifie si le nombre d'arguments est correct
	if (argc != 3)
	{
		printf("%s\n", "Usage argv[0] ServerIP ServerPort");
		exit(1);
	}

	// Initialise le socket client avant de lire le clavier ... pas une bonne idée
	int sockfd = initSocketClient(argv[1], atoi(argv[2]));

	printf("Bienvenue dans le programe vache - Entrez votre pseudo\n");

	// Crée un buffer pour stocker le message de l'utilisateur
	char msg[MESSAGE_SIZE];
	// Lit le message de l'utilisateur depuis l'entrée standard (clavier)
	sread(0, msg, 256);

	// Envoie le message de l'utilisateur au serveur
	swrite(sockfd, msg, sizeof(msg));

	/* attend la réponse du serveur */
	// Lit la réponse du serveur dans le buffer msg
	sread(sockfd, msg, sizeof(msg));

	printf("Réponse du serveur : \n");
	// Affiche la réponse du serveur
	printf("%s\n", msg);

	// Ferme le socket
	sclose(sockfd);

	return 0;
}