#include <stdio.h>
#include "messages.h"
#include "utils_v1.h"

int main(int argc, char const *argv[])
{

    char pseudo[MAX_PSEUDO];
	int sockfd;
	int ret;
    int* grille;
    int position;
    FILE *file = NULL;
    char **lines = NULL;

    //récupère les informations du fichier si il est passé en argument
    if(argc < 2){
        file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    int fd = fileno(file);
    char **lines = readFileToTable(fd);
    fclose(file);
    }

	StructMessage msg;
    StructMessage resp;

    // inscription du client
    printf("Bienvenue dans le programe d'inscription au serveur de jeu Streams\n");
	printf("Pour participer entrez votre nom/pseudo :\n");

    //recuperation du pseudo
    if(file!=NULL){
        //via le file donné en argument
    strncpy(pseudo, lines[0], MAX_PSEUDO);
            pseudo[MAX_PSEUDO - 1] = '\0';
    }else{
        //via l'entrée standard
	ret = sread(0, pseudo, MAX_PSEUDO);
	checkNeg(ret, "read client error");
	pseudo[ret - 1] = '\0';
    }

	strcpy(msg.messageText, pseudo);
	msg.code = INSCRIPTION_REQUEST;


    sockfd = initSocketClient(SERVER_IP, SERVER_PORT);
    //envoie la requete d'inscription au serveur et attend la reponse
    // * *msg nécessaire ou juste msg ?
    sendMessageAndReceiveResponse(sockfd, *msg.messageText);

    //traitement de la reponse reçue du serveur
    switch (msg.code)
        {
        case INSCRIPTION_OK:
            printf("Réponse du serveur : Inscription acceptée\n");
            break;
        case INSCRIPTION_KO:
            printf("Réponse du serveur : Inscription refusée\n");
            sclose(sockfd);
            exit(0);
        default:
            printf("Réponse du serveur non prévue %d\n", msg.code);
            break;
        }

    //si la partie commence
    if(msg.code==CURRENT_TUILE){
        //initialisation de la partie 
        grille = initializeBoard();
        int positionInFile = 1;

        while(msg.code==CURRENT_TUILE){
            //affichage de la grille
            displayBoard(grille);
            //affichage de la tuile courante
            printf("Tuile à placer  : %d\n", msg.tuile);
            printf("Entrez la position où vous voulez placer la tuile\n");

            //recuperation de la position de la tuile
                //via le file donné en argument
            if(file!=NULL){
                position = atoi(lines[positionInFile]);
                positionInFile++;
            }else{
                //via l'entrée standard
            scanf("%d", &position);
            }

            position = placeTile(grille, position, msg.tuile);

            printf("Tuile placée à la position  : %d\n", position);

	        msg.code = FINISHED_PLAYING;
            sendMessageAndReceiveResponse(sockfd, *msg.messageText);
        }
    }else{
		printf("PARTIE ANNULEE\n");
		sclose(sockfd);
        exit(0);
	}

    if(msg.code==FINISH_GAME){
        printf("FIN DE LA PARTIE\n");
        printf("Votre grille de jeu finale : \n");
        displayBoard(grille);
        int score = calculateScore(grille);
        printf("Votre score est de : %d\n", score);

        msg.code = FINAL_SCORE;
        sendMessageAndReceiveResponse(sockfd, *msg.messageText);

        if(msg.code==FINAL_RANKING){
            displayRanking(msg.scores);
        }

        if (lines != NULL) {
        for (size_t i = 0; lines[i] != NULL; ++i) {
            free(lines[i]); 
        }
        free(lines); 
    }
    }

    return 0;
}