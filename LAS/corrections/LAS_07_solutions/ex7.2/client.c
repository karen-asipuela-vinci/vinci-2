#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#include "utils_v1.h"

#define INPUT_FILE "sitemap.txt"
#define PERMS 0644
#define WEB_SERVER "ochoquet.be"
#define WEB_SERVER_PORT 80
#define BUFFER_SIZE 512
#define MSG_SIZE 1024

int initSocketClient(char ServerIP[16], int Serverport)
{
  int sockfd = ssocket();
  sconnect(ServerIP, Serverport, sockfd);
  return sockfd;
}

int main(int argc, char **argv)
{
  size_t nbChar;
  int fd;
  char pageName[BUFFER_SIZE];
  char ip[18];
  char request[BUFFER_SIZE];
  char ** lines;
  int i;
  char msg[MSG_SIZE];

  fd = sopen(INPUT_FILE, O_RDONLY, 0);

  hostname_to_ip(WEB_SERVER, ip);
  sprintf(msg,"IPv4 %s : %s\n", WEB_SERVER, ip);
  swrite(1,msg,strlen(msg));

  fd = sopen(INPUT_FILE,O_RDONLY,0);

  lines = readFileToTable(fd);
  sclose(fd);
  i = 0;

  while (lines[i] != NULL)
  {
    sprintf(msg,"Ligne : %s ", lines[i]);
    swrite(1,msg,strlen(msg));

    sprintf(pageName, "%s", strrchr(lines[i], '/') + 1);
    sprintf(msg,"Page Name : %s\n", pageName);
    swrite(1,msg,strlen(msg));

    int sockfd = initSocketClient(ip, WEB_SERVER_PORT);
    // No need to check: exit program on failure --> sconnect

    sprintf(request, "GET %s HTTP/1.0\r\nHost: %s\r\n\r\n", lines[i], WEB_SERVER);
    swrite(sockfd, request, strlen(request));

    int fdHTMLPage = sopen(pageName, O_RDWR | O_TRUNC | O_CREAT, PERMS);

    char response[BUFFER_SIZE];
    while ((nbChar = sread(sockfd, response, BUFFER_SIZE)) > 0)
    {
      swrite(fdHTMLPage, response, nbChar);
    }

    sclose(sockfd);
    sclose(fdHTMLPage);
    free(lines[i]);
    i++;
  

  }
  free(lines);
}
