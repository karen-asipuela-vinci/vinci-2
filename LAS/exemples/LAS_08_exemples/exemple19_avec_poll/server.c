#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>

#include "utils_v1.h"

#define MESSAGE_SIZE 8192
#define BACKLOG 5

// Cette fonction initialise un socket serveur et le lie à un port spécifié.
// En cas de succès, elle renvoie le descripteur de fichier du socket.
// En cas d'échec, elle affiche la cause de l'erreur et quitte le programme.
int initSocketServer(int port)
{
	int sockfd = ssocket();	  // Crée un nouveau socket
	sbind(port, sockfd);	  // Lie le socket au port spécifié
	slisten(sockfd, BACKLOG); // Met le socket en mode écoute
	return sockfd;			  // Renvoie le descripteur de fichier du socket
}

// Cette fonction renvoie un nom de monstre aléatoire.
static const char *random_monster()
{
	int random_number = rand() % 7 + 1;
	switch (random_number)
	{
	case 1:
		return "skeleton";
	case 2:
		return "stegosaurus";
	case 3:
		return "milk";
	case 4:
		return "bunny";
	case 5:
		return "duck";
	case 6:
		return "cock";
	case 7:
		return "dragon";
	}
	return "random number server ????";
}

// Cette fonction exécute le programme cowsay avec un monstre aléatoire et un message spécifié.
// Le résultat est écrit dans un fichier spécifié.
static void exec_cowsay(void *namefileV, void *msgV)
{
	char *namefile = (char *)namefileV;
	char *msg = (char *)msgV;

	int fd = sopen(namefile, O_WRONLY | O_TRUNC | O_CREAT, 0700);

	dup2(fd, 1);
	sexecl("/usr/games/cowsay", "cowsay", "-f", random_monster(), msg, NULL);
}

int main(int argc, char **argv)
{
	int sockfd, newsockfd, filefd;
	char buffer[MESSAGE_SIZE];
	int childpid;
	char namefile[1024];
	struct sockaddr_in addr;
	struct pollfd fds[1024];
	bool fds_invalid[1024];
	int nbSockfd = 0;
	int i, random_number;
	char msg[MESSAGE_SIZE];

	srand(time(NULL));

	if (argc != 2)
	{
		printf("%s\n", "Usage argv[0] ServerPort");
		exit(1);
	}

	sockfd = initSocketServer(atoi(argv[1]));
	printf("Le serveur est à l'écoute sur le port : %i \n", atoi(argv[1]));

	fds[nbSockfd].fd = sockfd;
	fds[nbSockfd].events = POLLIN;
	fds_invalid[nbSockfd] = false;
	nbSockfd++;

	while (1)
	{
		spoll(fds, nbSockfd, 0);

		// Si le socket d'écoute est prêt à lire (c'est-à-dire qu'une connexion entrante est en attente), accepte la nouvelle connexion.
		if (fds[0].revents & POLLIN && !fds_invalid[0])
		{
			newsockfd = saccept(sockfd);
			fds[nbSockfd].fd = newsockfd;
			fds[nbSockfd].events = POLLIN;
			fds_invalid[nbSockfd] = false;
			nbSockfd++;
		}

		// Traite les messages des clients
		for (i = 1; i < nbSockfd; i++)
		{
			if (fds[i].revents & POLLIN && !fds_invalid[i])
			{
				sread(fds[i].fd, msg, sizeof(msg));

				printf("MESSAGE RECU DE : %s - ADRESSE IP CLIENT : %s\n", msg, inet_ntoa(addr.sin_addr));

				if ((msg != NULL) && (strlen(msg) > 0))
				{
					time_t current_time;
					current_time = time(NULL);
					random_number = rand();
					sprintf(namefile, "%s_%i_%ld", "resultTest", random_number, current_time);
					childpid = fork_and_run2(exec_cowsay, namefile, msg);
					swaitpid(childpid, NULL, 0);
					memset(&buffer, 0, sizeof(buffer));
					filefd = sopen(namefile, O_RDONLY, 0700);
					sread(filefd, buffer, MESSAGE_SIZE);
					printf("REPONSE ENVOYEE PAR LE SERVEUR (doit être identique chez le client): \n");
					printf("%s\n", buffer);
					nwrite(fds[i].fd, buffer, sizeof(buffer));
					sclose(filefd);
				}
				else
				{
					sprintf(buffer, "message vide\n");
					nwrite(fds[i].fd, buffer, sizeof(buffer));
				}
				sleep(2);
				sclose(fds[i].fd);
				fds_invalid[i] = true;
			}
		}
	}
}