#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "messages.h"

#define PORT 1234 // Port to listen on

int main(void)
{
    int sockfd, newsockfd;
    socklen_t clilen;
    StructMessage buffer;
    struct sockaddr_in serv_addr, cli_addr;
    int n;

    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("ERROR opening socket");
        exit(1);
    }

    // Bind the socket to a port
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("ERROR on binding");
        exit(1);
    }

    // Listen for connections
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    // Accept a connection
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    if (newsockfd < 0)
    {
        perror("ERROR on accept");
        exit(1);
    }

    // Read the message from the client
    bzero(&buffer, 256);
    n = read(newsockfd, &buffer, 255);
    if (n < 0)
    {
        perror("ERROR reading from socket");
        exit(1);
    }

    printf("Received message: %d, %d\n", buffer.code, buffer.tuile);

    // Send a response to the client
    n = write(newsockfd, "I got your message", 18);
    if (n < 0)
    {
        perror("ERROR writing to socket");
        exit(1);
    }

    // Close the connections
    close(newsockfd);
    close(sockfd);

    return 0;
}