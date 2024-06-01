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
 * Basic sample that shows the different steps to have a listening server.
 *
 * In this sample, syscalls are not checked to concentrate on the different steps
 * but you must check the syscalls for the exercices !
 */

// Unsafe version as shown in videos
int main_unsafe_version(int argc, char *arg[])
{
  struct sockaddr_in addr;
  // socket creation
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  // setsockopt -> to avoid Address Already in Use
  int option = 1;
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(int));

  // prepare sockaddr to bind
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  // listen port 9090 !!!
  addr.sin_port = htons(PORT);
  // listen on all server interfaces
  addr.sin_addr.s_addr = htonl(INADDR_ANY);

  bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
  // simultaneous client max -> 5
  listen(sockfd, 5);
  printf("Le serveur tourne sur le port %d\n", PORT);
  // accept client connection
  int newsockfd = accept(sockfd, NULL, NULL);
  // read message from client
  int val;
  read(newsockfd, &val, sizeof(int));
  printf("Valeur reçue : %i\n", val);
  // close connection client
  close(newsockfd);
  // close listen socket
  close(sockfd);
}

// Safe version with safe functions
int main(int argc, char *arg[])
{
  struct sockaddr_in addr;

  // socket creation
  int sockfd = ssocket();
  sbind(PORT, sockfd);
  slisten(sockfd, BACKLOG);
  printf("Le serveur tourne sur le port %d\n", PORT);
  
  // accept client connection
  int newsockfd = saccept(sockfd);
  
  // read message from client
  int val;
  sread(newsockfd, &val, sizeof(int));
  printf("Valeur reçue : %i\n", val);
  
  // close connection client
  sclose(newsockfd);
  // close listen socket
  sclose(sockfd);
}
