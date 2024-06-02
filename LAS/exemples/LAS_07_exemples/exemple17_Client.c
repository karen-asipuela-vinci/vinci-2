#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "utils_v1.h"

#define LOCAL_HOST "127.0.0.1"
#define SERVER_PORT 9090
#define VAL 7

/**
 * Exemple basique qui montre les différentes étapes pour connecter un client
 * à un serveur.
 *
 * Dans cet exemple, les appels système ne sont pas vérifiés pour se concentrer sur les différentes étapes
 * mais vous devez vérifier les appels système pour les exercices !
 */

// !Version non sécurisée comme montré dans les vidéos
int main_unsafe_version(int argc, char *arg[])
{
  struct sockaddr_in addr;

  // création du socket
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  // préparation du socket pour la connexion
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;

  // connexion au port du serveur
  addr.sin_port = htons(SERVER_PORT);

  // connexion à l'adresse du serveur -> localhost
  inet_aton(LOCAL_HOST, &addr.sin_addr);                   // inet_aton convertit une adresse IPv4 en une forme binaire
  connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)); // connexion au serveur
  int val = VAL;
  printf("Le client envoie la valeur %d au serveur\n", VAL);
  write(sockfd, &val, sizeof(int)); // envoie de la valeur au serveur
  close(sockfd);                    // fermeture du socket
  return 0;
}

// Version sécurisée avec des fonctions sécurisées
int main(int argc, char *arg[])
{
  // socket creation
  int sockfd = ssocket();

  // prepare socket to connect
  sconnect(LOCAL_HOST, SERVER_PORT, sockfd);

  // write message to server
  int val = VAL;
  printf("Client envoie la valeur 7 au serveur\n");
  swrite(sockfd, &val, sizeof(int));

  // close socket
  sclose(sockfd);
  return 0;
}