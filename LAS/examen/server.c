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
    // doit lire le nom du client
    char buffer[MAX_SIZE];
    int ret;

    //* cast le paramètre en int
    int sockfd = *(int *)sockfdArg;

    // ! utiliser version safe, pas besoin de check
    ret = sread(sockfd, buffer, MAX_SIZE);
    // effacer dernier caractère
    buffer[ret - 1] = '\0';
    // on affiche le nom reçu
    printf("Nom client reçu : %s\n", buffer);

    // s'occupper de la mémoire partagée
    // appel à la mémoire
    int shm_id = sshmget(KEY, sizeof(clients), IPC_CREAT | PERM);
    // attachement pour STRUCTURE CLIENT
    struct clients *sh_client;
    sh_client = sshmat(shm_id);

    // ! comme mémoire partagé par plusieurs : utiliser sémaphore !!!
    int sem_id = sem_get(KEY, 1);
    // et on bloque
    sem_down0(sem_id);

    // on copie l'info voulue AVEC STRCPY (string)
    strcpy(sh_client->clients->name, buffer);
    sh_client->clients->sockfd = sockfd;
    sh_client->nbClients++;

    // on peut débloquer sémaphore
    sem_up0(sem_id);
    // détacher mémoire
    sshmdt(sh_client);
    // fermer socket
    sclose(sockfd);
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
    printf("la mémoire partagée contient :\n");
    printf("nb de clients : %d\n", ptrclients->nbClients);
    // tous les clients
    for (size_t i = 0; i < ptrclients->nbClients; i++)
    {
        // nom
        printf("nom client %ld : %s\n", i, ptrclients->clients[i].name);
        // sock
        printf("socket : %d\n", ptrclients->clients[i].sockfd);
    }
}

int main(int argc, char *arg[])
{
    struct clients *ptrclients;
    int nbClient = 0;

    ssigaction(SIGINT, sigint_handler);

    int sockfd = initSocketServer(9090);

    // TODO
    // initialiser la mémoire partagée
    int sh_id = sshmget(KEY, sizeof(clients), IPC_CREAT | PERM);
    // on attache à ce qu'on veut modifier
    ptrclients = sshmat(sh_id);

    // et on créé le sémaphore
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
            showSharedMemory(ptrclients);
            // delete mémoire
            sshmdelete(sh_id);
            exit(0);
        }
    }

    sclose(sockfd);
    return 0;
}
