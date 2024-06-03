#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "utils_v1.h"
#include "server.h"

volatile sig_atomic_t end = 0;

void clientHandler(void *sockfdArg)
{
    // TODO
    char name[MAX_SIZE];
    struct clients *ptrclients;

    int sockfd = *(int *)sockfdArg;

    int ret = sread(sockfd, name, MAX_SIZE);
    name[ret - 1] = '\0';
    printf("Nom client reçu : %s\n", name);

    int shm_id = sshmget(KEY, sizeof(clients), 0);
    ptrclients = sshmat(shm_id);
    int sem_id = sem_get(KEY, 1);
    sem_down0(sem_id);
    strcpy(ptrclients->clients[ptrclients->nbClients].name, name);
    ptrclients->clients[ptrclients->nbClients].sockfd = sockfd;
    ptrclients->nbClients++;
    sem_up0(sem_id);
    sshmdt(ptrclients);

    sclose(sockfd);
    exit(0);
}

int initSocketServer(int port)
{
    struct sockaddr_in addr;
    int sockfd = ssocket();

    sbind(port, sockfd);
    slisten(sockfd, BACKLOG);
    printf("Le serveur tourne sur le port %d\n", port);
    return sockfd;
}

void sigint_handler()
{
    printf("Fin serveur - Affichage des clients\n");
    end = 1;
}

void showSharedMemory(struct clients *ptrclients)
{
    // TODO
    printf("Nb clients : %d \n", ptrclients->nbClients);
    for (int i = 0; i < (ptrclients->nbClients); i++)
    {
        printf("Client name :  %s\n", ptrclients->clients[i].name);
        printf("Client sockfd :  %d\n", ptrclients->clients[i].sockfd);
    }
}

int main(int argc, char *arg[])
{
    struct clients *ptrclients;
    int nbClient = 0;

    ssigaction(SIGINT, sigint_handler);

    int sockfd = initSocketServer(9090);

    // TODO
    int shm_id = sshmget(KEY, sizeof(clients), IPC_CREAT | PERM);
    ptrclients = sshmat(shm_id);
    ptrclients->nbClients = 0;

    int sem_id = sem_create(KEY, 1, PERM, 1);

    while (1)
    {
        int newsockfd = accept(sockfd, NULL, NULL);

        if (newsockfd > 0)
        {
            // TODO
            fork_and_run1(clientHandler, &newsockfd);
        }

        if (end == 1)
        {
            // TODO
            showSharedMemory(ptrclients);
            sshmdelete(shm_id);
            exit(0);
        }
    }

    sclose(sockfd);
    return 0;
}