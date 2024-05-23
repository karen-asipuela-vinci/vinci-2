#include <stdio.h>
#include <string.h>
#include "messages.h"
#include "utils_v1.h"
#include <stdlib.h>
#include "network.h"
#include "jeu.h"

int main(int argc, char const *argv[])
{

    char pseudo[MAX_PSEUDO];
    int sockfd;
    int *grille;
    int position;
    int port = atoi(argv[1]);

    StructMessage msg;
    msg.scores = malloc(sizeof(Ranking));
    // malloc donc gestion d'erreur
    if (msg.scores == NULL)
    {
        printf("Erreur d'allocation de mémoire msg.scores\n");
        exit(0);
    }

    // inscription du client
    printf("Bienvenue dans le programe d'inscription au serveur de jeu Streams\n");
    printf("Pour participer entrez votre nom/pseudo :\n");

    // recuperation du pseudo
    scanf("%s", pseudo);
    printf("Bienvenue, %s\n", pseudo);
    strcpy(msg.messageText, pseudo);
    // test autre copie
    strncpy(msg.scores->scores[0].pseudo, pseudo, MAX_PSEUDO - 1);
    msg.scores->scores[0].pseudo[MAX_PSEUDO - 1] = '\0';

    msg.code = INSCRIPTION_REQUEST;

    sockfd = initSocketClient(SERVER_IP, port);
    // envoie la requete d'inscription au serveur et attend la reponse
    //  * *msg nécessaire ou juste msg ?
    sendMessageAndReceiveResponse(sockfd, &msg);
    // traitement de la reponse reçue du serveur
    switch (msg.code)
    {
    case INSCRIPTION_OK:
        printf("Réponse du serveur : Inscription acceptée\n");
        break;
    case INSCRIPTION_KO:
        printf("Réponse du serveur : Inscription refusée\n");
        sclose(sockfd);
        exit(0);
    case CANCEL_GAME:
        printf("Réponse du serveur : pas assez de joueurs\n");
        sclose(sockfd);
        exit(0);
    default:
        printf("Réponse du serveur non prévue %d\n", msg.code);
        break;
    }

    sread(sockfd, &msg, sizeof(msg));

    // si la partie commence
    if (msg.code == CURRENT_TUILE)
    {
        // initialisation de la partie
        grille = initializeBoard();

        while (msg.code == CURRENT_TUILE)
        {
            // affichage de la grille
            displayBoard(grille);
            // affichage de la tuile courante
            printf("Tuile à placer  : %d\n", msg.tuile);
            printf("Entrez la position où vous voulez placer la tuile\n");

            scanf("%d", &position);

            position = placeTile(grille, position, msg.tuile);
            displayBoard(grille);

            printf("Tuile placée à la position  : %d\n", position + 1);

            msg.code = FINISHED_PLAYING;
            sendMessageAndReceiveResponse(sockfd, &msg);
        }
    }
    else
    {
        printf("PARTIE ANNULEE\n");
        sclose(sockfd);
        exit(0);
    }

    if (msg.code == FINISH_GAME)
    {
        printf("FIN DE LA PARTIE\n");
        printf("Votre grille de jeu finale : \n");
        displayBoard(grille);
        int score = calculateScore(grille);
        printf("Votre score est de : %d\n", score);

        msg.code = FINAL_SCORE;
        msg.tuile = score;
        sendMessageAndReceiveResponse(sockfd, &msg);
        // sread(sockfd, &msg, sizeof(msg));
        printColor("%s", "CODE FIN DE FINISG_GAME", GREEN_TEXT);
        printf("msg.code : %d\n", msg.code);
    }

    if (msg.code == FINAL_RANKING)
    {
        printf("in FINAL_RANKING\n");
        msg.code = FINAL_RANKING;
        sendMessageAndReceiveResponse(sockfd, &msg);
        printf("msg.code : %d\n", msg.code);
        printf("Nombre de joueurs : %d\n", msg.scores->nbPlayers);
        printf("scores[0].score : %d\n", msg.scores->scores[0].score);
        displayScore(msg.scores);
    }

    // sclose(sockfd);
    return 0;
}