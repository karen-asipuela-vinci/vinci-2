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
#define TIME_INSCRIPTION 5

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
    sclose(player->pipefd_read[1]);  // Close write end of read pipe
    sclose(player->pipefd_write[0]); // Close read end of write pipe
}

void childProcess(void *arg)
{
    int i = *(int *)arg;
    StructMessage msg;
    msg.scores = malloc(sizeof(Ranking));
    handlePlayerCommunication(&tabPlayers[i]); // Gérer la communication avec le joueur

    // arrete de passer dans la boucle apres avoir gere le message de fin de partie
    while (msg.code != FINAL_SCORE)
    {
        // recuperation du message envoyé par le serveur
        sread(tabPlayers[i].pipefd_read[0], &msg, sizeof(msg));
        // envoi du message au client et attente de la réponse
        sendMessageAndReceiveResponse(tabPlayers[i].sockfd, &msg);
        // envoi de la réponse du client au serveur
        nwrite(tabPlayers[i].pipefd_write[1], &msg, sizeof(msg));
    }
    nwrite(tabPlayers[i].pipefd_write[1], &msg, sizeof(msg));
    printf("nbPlayers 100 : %d\n", msg.scores->nbPlayers);

    // recupere le semaphore
    int sem = getSemaphoreID();
    // down sur le semaphore
    sem_down0(sem);
    // recupere les scores quand il a acces a la memoire partagée
    int shm_id = sshmget(SHM_KEY, sizeof(Ranking), 0);
    Ranking *rankingSHM = (Ranking *)sshmat(shm_id);
    printf("DANS LE PROCESSUS FILS - memoire partagée\n");
    printf("NOMBRE DE JOUEURS DANS SHM - FILS : %d\n", rankingSHM->nbPlayers);
    printf("SCORES DU JOUEUR %s : %d\n", rankingSHM->scores[0].pseudo, rankingSHM->scores[0].score);

    // rend l'accès à la mémoire partagée
    sem_up(sem, 0);

    printf("ENVOI DU RANKING AU CLIENT---------------------------------\n");
    // envoi du ranking final au client
    msg.code = FINAL_RANKING;
    memcpy(msg.scores, rankingSHM, sizeof(Ranking));
    printf("nbPlayers : %d\n", msg.scores->nbPlayers);
    printf("score de %d : %d\n", i, msg.scores->scores[i].score);
    sendMessageAndReceiveResponse(tabPlayers[i].sockfd, &msg);
    if (msg.code == FINAL_RANKING)
    {
        printf("message envoyé\n");
    }
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
    if (scores == NULL)
    {
        perror("Erreur lors de l'initialisation de la mémoire partagée");
        exit(EXIT_FAILURE);
    }

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
        sclose(sockfd);
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

        sclose(tabPlayers[i].pipefd_read[0]);  // Fermer l'extrémité de lecture du pipe de lecture
        sclose(tabPlayers[i].pipefd_write[1]); // Fermer l'extrémité d'écriture du pipe d'écriture
    }

    // GAME PART
    int nbTurnsPlayed = 0;
    int currentTuile;
    int *tuiles = initializeTiles();
    struct pollfd poll_fds[MAX_PLAYERS];

    // Initialiser les structures pollfd pour surveiller les pipes d'écriture des processus enfants
    for (i = 0; i < nbPlayers; i++)
    {
        poll_fds[i].fd = tabPlayers[i].pipefd_write[0]; // le pipe d'écriture du processus enfant
        poll_fds[i].events = POLLIN;                    // Surveiller les événements d'écriture
    }

    while (nbTurnsPlayed < 20)
    {
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
            nwrite(tabPlayers[i].pipefd_read[1], &msg, sizeof(msg));
        }

        // TODO polls
        // bool playersSentPosition[MAX_PLAYERS] = {false};
        int numPlayersReady = 0;

        // Attendre que tous les joueurs confirment qu'ils ont reçu la tuile actuelle
        while (numPlayersReady < nbPlayers)
        {
            int poll_result = spoll(poll_fds, nbPlayers, 5);

            if (poll_result > 0)
            {
                // printf("poll result %d\n", poll_result);
                for (i = 0; i < nbPlayers; i++)
                {
                    // Un des processus enfants a envoyé un message
                    // et le joueur n'a pas encore envoyé sa position pour ce tour
                    if ((poll_fds[i].revents & POLLIN))
                    { // && playersSentPosition[i]) {
                        sread(tabPlayers[i].pipefd_write[0], &msg, sizeof(msg));
                        // traitez la position de tuile recue du serveur fils
                        if (msg.code == FINISHED_PLAYING)
                        {
                            // Marquez le joueur comme ayant envoyé sa position pour ce tour
                            // playersSentPosition[i] = true;
                            numPlayersReady++;
                        }
                    }
                }
            }
            else
            {
                // gerer l'erreur
                //  printf("noon\n");
            }
        }
        for (i = 0; i < MAX_PLAYERS; i++)
        {
            // playersSentPosition[i] = false;
        }
        nbTurnsPlayed++;
    }

    // END OF GAME PART
    msg.code = FINISH_GAME;
    for (i = 0; i < nbPlayers; i++)
    {
        nwrite(tabPlayers[i].pipefd_read[1], &msg, sizeof(msg));
    }

    // RANKING SCORES
    printf("IN RANKING SCORES\n");
    printf("print scores\n");
    for (int i = 0; i < nbPlayers; i++)
    {
        printf("score : %d de %s\n", scores->scores[i].score, scores->scores[i].pseudo);
    }

    int numScoreReady = 0;
    Ranking preranking[MAX_PLAYERS];

    preranking->nbPlayers = nbPlayers;

    for (int i = 0; i < nbPlayers; i++)
    {
        strncpy(preranking->scores[i].pseudo, tabPlayers[i].pseudo, MAX_PSEUDO - 1);
        preranking->scores[i].pseudo[MAX_PSEUDO - 1] = '\0';
        preranking->scores[i].score = -1;
    }

    // Attendre que tous les joueurs confirment qu'ils ont reçu la tuile actuelle
    while (numScoreReady < nbPlayers)
    {
        int poll_result = spoll(poll_fds, nbPlayers, 5);

        if (poll_result > 0)
        {
            for (i = 0; i < nbPlayers; i++)
            {
                // Vérifiez si le pipe de lecture du processus fils est prêt pour la lecture
                if ((poll_fds[i].revents & POLLIN && preranking->scores[i].score == -1))
                {
                    printf("in pollin\n");
                    // Lire le message du processus fils
                    sread(tabPlayers[i].pipefd_write[0], &msg, sizeof(msg));
                    // Traitez la position de tuile reçue du processus fils
                    if (msg.code == FINAL_SCORE)
                    {
                        tabPlayers[i].score = msg.tuile;
                        // Marquez le joueur comme ayant envoyé sa position pour ce tour
                        preranking->scores[i].score = msg.tuile;
                        numScoreReady++;
                    }
                }
            }
        }
        else
        {
            // Gérer l'erreur de poll
        }
    }

    // TRI DES SCORES
    scores->nbPlayers = preranking->nbPlayers;
    printf("avant tri, nbre de jouers: %d\n", scores->nbPlayers);
    for (int i = 0; i < scores->nbPlayers; i++)
    {
        scores->scores[i] = preranking->scores[i];
        printf("scoooore : %d\n", scores->scores[i].score);
        printf("de : %s\n", scores->scores[i].pseudo);
        printf("nbPlayers : %d\n", scores->nbPlayers);
    }

    printf("sortie de tri, nbre de jouers: %d\n", scores->nbPlayers);
    Ranking *sortedRanking = sortRanking(scores);
    printf("sortie de sortRanking\n");
    // rend accès à la mémoire partagée
    sem_up(sem, 0);

    // liberation des différentes ressources a la fin du programme
    for (i = 0; i < nbPlayers; i++)
    {
        sclose(tabPlayers[i].pipefd_read[1]);  // Fermeture du côté lecture du pipe
        sclose(tabPlayers[i].pipefd_write[0]); // Fermeture du côté écriture du pipe
    }

    if (lines != NULL)
    {
        for (size_t i = 0; lines[i] != NULL; ++i)
        {
            free(lines[i]);
        }
        free(lines);
    }

    sshmdt(sortedRanking);
    disconnect_players(tabPlayers, nbPlayers);
    sclose(sockfd);
    // TODO : check si bien FINAL_RANKING ou RANKING ???

    return 0;
}