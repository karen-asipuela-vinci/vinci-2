#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "utils_v1.h"
#include "messages.h"
#include "score.h"
#include "network.h"
#include "ipc.h"
#include "jeu.h"
#include "ranking.h"
#include <sys/socket.h>

#define MAX_PLAYERS 4
#define MIN_PLAYERS 2
// TODO PUT 30
#define TIME_INSCRIPTION 20

Player tabPlayers[MAX_PLAYERS];
volatile sig_atomic_t end_inscriptions = 0;

void endServerHandler(int sig)
{
    end_inscriptions = 1;
}

void handlePlayerCommunication(Player *player)
{

    // Child process
    // Close unused ends of the pipes
    int closeChild1 = sclose(player->pipefd_read[1]);  // Close write end of read pipe
    int closeChild2 = sclose(player->pipefd_write[0]); // Close read end of write pipe

    if (closeChild1 == -1 || closeChild2 == -1)
    {
        perror("Erreur lors de la fermeture des extrémités de pipe - enfants");
        exit(EXIT_FAILURE);
    }
}

void childProcess(void *arg)
{
    int i = *(int *)arg;
    StructMessage msg;
    handlePlayerCommunication(&tabPlayers[i]); // Gérer la communication avec le joueur

    // arrete de passer dans la boucle apres avoir gere le message de fin de partie
    while (msg.code != FINISH_GAME)
    {
        // recuperation du message envoyé par le serveur
        printf("lit info serveur\n");
        int read = sread(tabPlayers[i].pipefd_read[0], &msg, sizeof(msg));
        if (read == -1)
        {
            perror("Erreur lors de la lecture du message du serveur");
            exit(EXIT_FAILURE);
        }

        // envoi du message au client et attente de la réponse
        printf("comm client\n");
        sendMessageAndReceiveResponse(tabPlayers[i].sockfd, &msg);
        // envoi de la réponse du client au serveur
        printf("envoie reponse au serveur\n");
        nwrite(tabPlayers[i].pipefd_write[1], &msg, sizeof(msg));
        printf("fin de serv-fils-serv\n");
    }

    // recupere le semaphore
    int sem = getSemaphoreID();
    // down sur le semaphore
    sem_down(sem, 0);
    // recupere les scores quand il a acces a la memoire partagée
    int shm_id = sshmget(SHM_KEY, sizeof(Ranking), 0);
    Ranking *ranking = (Ranking *)sshmat(shm_id);
    // rend l'accès à la mémoire partagée
    sem_up(sem, 0);

    // envoi du ranking final au client
    msg.code = FINAL_RANKING;
    msg.scores = ranking;
    swrite(tabPlayers[i].sockfd, &msg, sizeof(&msg));

    free(arg);

    exit(21);
}

int main(int argc, char const *argv[])
{
    int sockfd, newsockfd, i;
    StructMessage msg;
    int ret;
    // struct pollfd fds[MAX_PLAYERS];
    FILE *file = NULL;
    char **lines = NULL;
    Ranking *scores = NULL;
    int port = atoi(argv[1]);

    // récupère les informations du fichier si il est passé en argument
    if (argc >= 3)
    {
        file = fopen(argv[2], "r");
        if (file == NULL)
        {
            perror("Error opening file");
            return 1;
        }
        int fd = fileno(file);
        lines = readFileToTable(fd);
        fclose(file);
    }

    ssigaction(SIGALRM, endServerHandler);
    ssigaction(SIGINT, endServerHandler);

    sockfd = initSocketServer(port);
    printf("Le serveur tourne sur le port : %i \n", port);

    // initialisation de la mémoire partagée
    scores = initializeSharedMemory();
    int sem = initializeSemaphores();

    i = 0;
    int nbPlayers = 0;

    // INSCRIPTION PART
    alarm(TIME_INSCRIPTION);
    while (!end_inscriptions && nbPlayers < MAX_PLAYERS)
    {
        newsockfd = accept(sockfd, NULL, NULL);
        if (newsockfd > 0)
        {
            ret = sread(newsockfd, &msg, sizeof(msg));

            if (ret == -1)
            {
                perror("Erreur lors de la lecture du message");
                exit(EXIT_FAILURE);
            }

            if (msg.code == INSCRIPTION_REQUEST)
            {
                strcpy(tabPlayers[i].pseudo, msg.messageText);
                tabPlayers[i].sockfd = newsockfd;

                if (nbPlayers < MAX_PLAYERS)
                {
                    msg.code = INSCRIPTION_OK;
                    swrite(tabPlayers[i].sockfd, &msg, sizeof(msg));
                    if (nbPlayers == MAX_PLAYERS)
                    {
                        alarm(0); // cancel alarm
                        end_inscriptions = 1;
                    }
                }
                else
                {
                    msg.code = INSCRIPTION_KO;
                    swrite(tabPlayers[i].sockfd, &msg, sizeof(msg));
                }

                // Création des pipes bidirectionnels pour la communication avec le serveur fils
                int pipefd[2];
                int pipefd2[2];
                if ((spipe(pipefd) == -1) || (spipe(pipefd2) == -1))
                {
                    perror("Erreur lors de la création des pipes");
                    exit(EXIT_FAILURE);
                }

                tabPlayers[i].pipefd_read[0] = pipefd[0];
                tabPlayers[i].pipefd_read[1] = pipefd[1];
                tabPlayers[i].pipefd_write[0] = pipefd2[0];
                tabPlayers[i].pipefd_write[1] = pipefd2[1];

                nbPlayers++;
                printf("Nb Inscriptions : %i\n", nbPlayers);
                i++;
            }
        }
    }

    // END OF INSCRIPTION PART
    // CHECK IF ENOUGH PLAYERS REGISTERED
    printf("FIN DES INSCRIPTIONS\n");
    if (nbPlayers < MIN_PLAYERS)
    {
        printf("PARTIE ANNULEE .. PAS ASSEZ DE JOUEURS\n");
        msg.code = CANCEL_GAME;
        for (i = 0; i < nbPlayers; i++)
        {
            sendMessageAndReceiveResponse(tabPlayers[i].sockfd, &msg);
        }
        disconnect_players(tabPlayers, nbPlayers);
        int closeSock = sclose(sockfd);
        if (closeSock == -1)
        {
            perror("Erreur lors de la fermeture du socket");
            exit(EXIT_FAILURE);
        }
        exit(0);
    }

    for (i = 0; i < nbPlayers; i++)
    {
        int *arg = malloc(sizeof(int));
        *arg = i;
        // Création du processus fils
        pid_t pid = fork_and_run1(childProcess, arg);

        if (pid == -1)
        {
            perror("Erreur lors de la création du processus fils");
            exit(EXIT_FAILURE);
        }

        int close1 = sclose(tabPlayers[i].pipefd_read[0]);  // Fermer l'extrémité de lecture du pipe de lecture
        int close2 = sclose(tabPlayers[i].pipefd_write[1]); // Fermer l'extrémité d'écriture du pipe d'écriture
        if (close1 == -1 || close2 == -1)
        {
            perror("Erreur lors de la fermeture des extrémités de pipe");
            exit(EXIT_FAILURE);
        }
    }

    // GAME PART
    int nbTurnsPlayed = 0;
    int currentTuile;
    int *tuiles = initializeTiles();
    struct pollfd poll_fds[MAX_PLAYERS];

    // Initialiser les structures pollfd pour surveiller les pipes d'écriture des processus enfants
    for (i = 0; i < nbPlayers; i++)
    {
        poll_fds[i].fd = tabPlayers[i].pipefd_read[0]; // le pipe d'écriture du processus enfant
        poll_fds[i].events = POLLIN;
        poll_fds[i].revents = 0;
    }

    while (nbTurnsPlayed < 21)
    {
        printf("!!!!!!!!!!!!!!!20!!!!!!!!!!!!!!");
        // PICK A TILE
        // in the given file
        if (file != NULL)
        {
            currentTuile = atoi(lines[nbTurnsPlayed]);
        }
        else
        {
            // randomly
            currentTuile = drawRandomTile(tuiles);
            printf("tuile a placer: %d \n", currentTuile);
        }

        // SEND THE TILE TO ALL PLAYERS
        msg.code = CURRENT_TUILE;
        msg.tuile = currentTuile;

        for (i = 0; i < nbPlayers; i++)
        {
            printf("meow\n");
            nwrite(tabPlayers[i].pipefd_read[1], &msg, sizeof(msg));
            printf("coin\n");
        }

        // TODO polls
        bool playersSentPosition[MAX_PLAYERS] = {false};
        printf("playersSentPosition: %d\n", playersSentPosition[0]);
        int numPlayersReady = 0;

        // Attendre que tous les joueurs confirment qu'ils ont reçu la tuile actuelle
        while (numPlayersReady < nbPlayers)
        {
            int poll_result = spoll(poll_fds, nbPlayers, 0);
            printf("poll result: %d\n", poll_result);
            if (poll_result > 0)
            {
                printf("/////////////////////////");
                // !ATTENTION A PARTIR D'ICI
                for (i = 0; i < nbPlayers; i++)
                {

                    printf("i: %d\n", i);
                    printf("poll_fd: %d\n", poll_fds[i].fd);
                    //*check si pollhup
                    if (poll_fds[i].revents & POLLHUP)
                    {
                        printf("Déconnexion détectée sur le descripteur de fichier: %d\n", poll_fds[i].fd);
                        printf("Player %d disconnected\n", i);
                    }
                    //! rajouter !playersSentPosition[i]
                    //*check si pollin
                    else if (poll_fds[i].revents & POLLIN)
                    {
                        printf("POLLIN défini, données dispo en lecture\n");
                        int read = sread(tabPlayers[i].pipefd_read[0], &msg, sizeof(msg));
                        if (read == -1)
                        {
                            perror("Erreur lors de la lecture du message du serveur");
                            exit(EXIT_FAILURE);
                        }
                        // traitez la position de tuile recue du serveur fils
                        if (msg.code == FINISHED_PLAYING)
                        {
                            // Marquez le joueur comme ayant envoyé sa position pour ce tour
                            playersSentPosition[i] = true;
                            numPlayersReady++;
                        }
                    }
                    else if (poll_fds[i].revents && POLLERR)
                    {
                        printf("Erreur détectée sur le descripteur de fichier: %d\n", poll_fds[i].fd);
                    }
                }
            }
            else
            {
                // gerer l'erreur
                printf("keske jfous la\n");
            }

            numPlayersReady++;

            for (i = 0; i < MAX_PLAYERS; i++)
            {
                playersSentPosition[i] = false;
            }
            nbTurnsPlayed++;
        }
    }
    // END OF GAME PART
    msg.code = FINISH_GAME;
    for (i = 0; i < nbPlayers; i++)
    {
        nwrite(tabPlayers[i].pipefd_read[1], &msg, sizeof(msg));
    }

    // TRI DES SCORES
    Ranking *sortedRanking = sortRanking(scores);
    // rend accès à la mémoire partagée
    sem_up(sem, 0);

    // liberation des différentes ressources a la fin du programme
    for (i = 0; i < nbPlayers; i++)
    {
        int close1 = sclose(tabPlayers[i].pipefd_read[0]);  // Fermeture du côté lecture du pipe
        int close2 = sclose(tabPlayers[i].pipefd_write[1]); // Fermeture du côté écriture du pipe

        if (close1 == -1 || close2 == -1)
        {
            perror("Erreur lors de la fermeture des extrémités de pipe");
            exit(EXIT_FAILURE);
        }
    }

    if (lines != NULL)
    {
        for (size_t i = 0; lines[i] != NULL; ++i)
        {
            free(lines[i]);
        }
        free(lines);
    }

    disconnect_players(tabPlayers, nbPlayers);
    sclose(sockfd);
    // TODO : check si bien FINAL_RANKING ou RANKING ???
    sshmdt(sortedRanking);

    return 0;
}