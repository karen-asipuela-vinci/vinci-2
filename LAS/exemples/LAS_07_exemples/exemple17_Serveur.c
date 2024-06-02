#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "utils_v1.h"

#define BACKLOG 5
#define PORT 9090

/**
 * Exemple basique qui montre les différentes étapes pour avoir un serveur en écoute.
 *
 * Dans cet exemple, les appels système ne sont pas vérifiés pour se concentrer sur les différentes étapes
 * ! mais vous devez vérifier les appels système pour les exercices !
 */

// ! Version non sécurisée comme montré dans les vidéos
int main_unsafe_version(int argc, char *arg[])
{
  struct sockaddr_in addr;
  // création du socket
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  // setsockopt -> pour éviter l'erreur "Adresse déjà utilisée"
  int option = 1;
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(int));

  // préparation de sockaddr pour le bind
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  // écoute sur le port 9090 !!!
  addr.sin_port = htons(PORT);
  // écoute sur toutes les interfaces du serveur
  addr.sin_addr.s_addr = htonl(INADDR_ANY);

  bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
  // nombre maximum de clients simultanés -> 5
  listen(sockfd, 5);
  printf("Le serveur tourne sur le port %d\n", PORT);
  // acceptation de la connexion client
  int newsockfd = accept(sockfd, NULL, NULL);
  // lecture du message du client
  int val;
  read(newsockfd, &val, sizeof(int));
  printf("Valeur reçue : %i\n", val);
  // fermeture de la connexion client
  close(newsockfd);
  // fermeture du socket d'écoute
  close(sockfd);
}

// ! Version sécurisée avec des fonctions sécurisées
int main(int argc, char *arg[])
{
  struct sockaddr_in addr;

  // création du socket
  int sockfd = ssocket();
  sbind(PORT, sockfd);
  slisten(sockfd, BACKLOG);
  printf("Le serveur tourne sur le port %d\n", PORT);

  // acceptation de la connexion client
  int newsockfd = saccept(sockfd);

  // lecture du message du client
  int val;
  sread(newsockfd, &val, sizeof(int));
  printf("Valeur reçue : %i\n", val);

  // fermeture de la connexion client
  sclose(newsockfd);
  // fermeture du socket d'écoute
  sclose(sockfd);
}