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
 * Basic sample that shows the different steps to have a client connected 
 * to a server.
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
  
  // prepare socket to connect
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  
  // connect to server port
  addr.sin_port = htons(SERVER_PORT);
  
  // connect to server address -> localhost
  inet_aton(LOCAL_HOST,&addr.sin_addr);
  connect(sockfd, (struct sockaddr *) &addr, sizeof(addr));
  int val = VAL;
  printf("Client envoie la valeur %d au serveur\n",VAL);
  write(sockfd,&val,sizeof(int));
  close(sockfd);
  return 0;
}

// Safe version with safe functions
int main(int argc, char *arg[]) 
{
  // socket creation
  int sockfd = ssocket();
  
  // prepare socket to connect
  sconnect(LOCAL_HOST, SERVER_PORT, sockfd);
  
  // write message to server
  int val = VAL;
  printf("Client envoie la valeur 7 au serveur\n");
  swrite(sockfd,&val,sizeof(int));
  
  // close socket
  sclose(sockfd);
  return 0;
}