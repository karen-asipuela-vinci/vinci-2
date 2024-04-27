#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "utils_v1.h"
#include "messages.h"
#include "player.h"
#include "score.h"
#include "network.h"
#include "ipc.h"
#include "jeu.h"


#define MAX_PLAYERS 4
#define MIN_PLAYERS 2
#define TIME_INSCRIPTION 30



Player tabPlayers[MAX_PLAYERS];
volatile sig_atomic_t end_inscriptions = 0;

void endServerHandler(int sig)
{
	end_inscriptions = 1;
}

void handlePlayerCommunication(Player *player) {
    // Child process
    // Close unused ends of the pipes
    close(player->pipefd[1]);  // Close write end of read pipe
    close(player->pipefd[0]); // Close read end of write pipe
    // Redirect standard input/output to the pipes
    dup2(player->pipefd[0], STDIN_FILENO);   // Replace stdin with read end of read pipe
    dup2(player->pipefd[1], STDOUT_FILENO); // Replace stdout with write end of write pipe

 }



void childProcess(void *arg) {
    int i = *(int*)arg;
    StructMessage msg;

    /* Dans le processus enfant */
    handlePlayerCommunication(&tabPlayers[i]); // Gérer la communication avec le joueur

    //arrete de passer dans la boucle apres avoir gere le message de fin de partie
    while (msg.code != FINISH_GAME){
        //recuperation du message envoyé par le serveur
        sread(tabPlayers[i].sockfd, &msg, sizeof(msg));
        //envoi du message au client et attente de la réponse
        sendMessageAndReceiveResponse(tabPlayers[i].sockfd, &msg);
        //envoi de la réponse du client au serveur
        nwrite(tabPlayers[i].sockfd, &msg, sizeof(msg));
    }

    //recupere le semaphore
    int sem = getSemaphoreID();
    //down sur le semaphore
    sem_down(sem, 0);
    //recupere les scores quand il a acces a la memoire partagée
    int shm_id = sshmget(SHM_KEY, sizeof(Ranking), 0);
    Ranking* ranking = (Ranking*)sshmat(shm_id);
    //rend l'accès à la mémoire partagée
    sem_up(sem, 0);

    //envoi du ranking final au client
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
	//int ret;
	//struct pollfd fds[MAX_PLAYERS];
    FILE *file = NULL;
    char **lines = NULL;
    Ranking* scores = NULL;


    //récupère les informations du fichier si il est passé en argument
    if(argc < 2){
        file = fopen(argv[1], "r");
        if (file == NULL) {
            perror("Error opening file");
            return 1;
        }
        // int fd = fileno(file);
        // char **lines = readFileToTable(fd);
        fclose(file);
    }

	ssigaction(SIGALRM, endServerHandler);
	ssigaction(SIGINT, endServerHandler);

	sockfd = initSocketServer(SERVER_PORT);
	printf("Le serveur tourne sur le port : %i \n", SERVER_PORT);

    //initialisation de la mémoire partagée
    scores = initializeSharedMemory();
    int sem = initializeSemaphores();

    i = 0;
	int nbPlayers = 0;

	// INSCRIPTION PART
	alarm(TIME_INSCRIPTION);
    while (!end_inscriptions && nbPlayers < MAX_PLAYERS)
    {
        newsockfd = saccept(sockfd);
        if (newsockfd > 0)
        {
           int ret = sread(newsockfd, &msg, sizeof(msg));
           
            if (ret == -1)
            {
                perror("Erreur lors de la lecture du message");
                exit(EXIT_FAILURE);
            }

            if (msg.code == INSCRIPTION_REQUEST)
            {
                strcpy(tabPlayers[i].pseudo, msg.messageText);
                tabPlayers[i].sockfd = newsockfd;
                // Création des pipes bidirectionnels pour la communication avec le serveur fils
                int pipefd[2];
                int pipefd2[2];
                if (spipe(pipefd) == -1 || spipe(pipefd2) == -1) {
                    perror("Erreur lors de la création des pipes");
                    exit(EXIT_FAILURE);
                }
                tabPlayers[i].pipefd[0] = pipefd[0]; 
                tabPlayers[i].pipefd[1] = pipefd[1];
                nbPlayers++;
                printf("Nb Inscriptions : %i\n", nbPlayers);
                i++;
            }
        }
    }

    //END OF INSCRIPTION PART
    //CHECK IF ENOUGH PLAYERS REGISTERED
    printf("FIN DES INSCRIPTIONS\n");
	if (nbPlayers < MIN_PLAYERS)
	{
		printf("PARTIE ANNULEE .. PAS ASSEZ DE JOUEURS\n");
		msg.code = CANCEL_GAME;
		for (i = 0; i < nbPlayers; i++)
		{
			swrite(tabPlayers[i].sockfd, &msg, sizeof(msg));
		}
		disconnect_players(tabPlayers, nbPlayers);
		sclose(sockfd);
		exit(0);
	}

     for (i = 0; i < nbPlayers; i++){
        int* arg = malloc(sizeof(int));
        *arg = i;
        // Création du processus fils
        pid_t pid = fork_and_run1(childProcess, arg);

        if (pid == -1) {
            perror("Erreur lors de la création du processus fils");
            exit(EXIT_FAILURE);
        }
      
        handlePlayerCommunication(&tabPlayers[i]); // Gérer la communication avec le joueur
      
        close(tabPlayers[i].pipefd[0]);   // Fermer l'extrémité de lecture du pipe de lecture
        close(tabPlayers[i].pipefd[1]);  // Fermer l'extrémité d'écriture du pipe d'écriture
    }
    

    //GAME PART
	// int nbPlayersAlreadyPlayed = 0;
    int nbTurnsPlayed = 0;
    int currentTuile;
    int* tuiles = initializeTiles();
    struct pollfd poll_fds[MAX_PLAYERS];

   // Initialiser les structures pollfd pour surveiller les pipes d'écriture des processus enfants
    for (i = 0; i < nbPlayers; i++) {
    poll_fds[i].fd = tabPlayers[i].pipefd[1]; //le pipe d'écriture du processus enfant
    poll_fds[i].events = POLLOUT; //Surveiller les événements d'écriture
    }
   
    while(nbTurnsPlayed < 20){
        // PICK A TILE
            // in the given file
        if(file!=NULL){
            currentTuile = atoi(lines[nbTurnsPlayed+1]);
        }else{
            //randomly
            currentTuile = drawRandomTile(tuiles);
        }

        //SEND THE TILE TO ALL PLAYERS
        msg.code=CURRENT_TUILE;
        msg.tuile = currentTuile;

        for (i = 0; i < nbPlayers; i++){
            nwrite(tabPlayers[i].pipefd[1], &msg,sizeof(msg));
        }

    //TODO polls
    bool playersSentPosition[MAX_PLAYERS] = {false};
    int numPlayersReady = 0;
    
    // Attendre que tous les joueurs confirment qu'ils ont reçu la tuile actuelle
    while (numPlayersReady < nbPlayers) {
        int poll_result = spoll(poll_fds, nbPlayers, 0); 

        if (poll_result > 0) {
            for (i = 0; i < nbPlayers; i++) {
                    // Un des processus enfants a envoyé un message
                    // et le joueur n'a pas encore envoyé sa position pour ce tour
                if ((poll_fds[i].revents & POLLOUT) && !playersSentPosition[i]) {
                
                    sread(tabPlayers[i].pipefd[0], &msg, sizeof(msg));
                    // traittez la potition de tuile recu du serveur fils
                    if(msg.code == FINISHED_PLAYING){
                    // Marquez le joueur comme ayant envoyé sa position pour ce tour
                    playersSentPosition[i] = true;
                    numPlayersReady++;
                    }
                }
            }
        } else {
            //gerer l'erreur
        }
}
    for(i = 0; i < MAX_PLAYERS; i++){
        playersSentPosition[i] = false;
    }
    nbTurnsPlayed ++;
    }

    //END OF GAME PART
    msg.code = FINISH_GAME;
      for (i = 0; i < nbPlayers; i++){
            // TODO : check si faux
            write(tabPlayers[i].pipefd[1], msg.messageText, strlen(msg.messageText) + 1);
        }


    //TRI DES SCORES 
    Ranking *sortedRanking = sortRanking(scores);
    // rend accès à la mémoire partagée
    sem_up(sem, 0);

    // liberation des différentes ressources a la fin du programme
    for (i = 0; i < nbPlayers; i++) {
        close(tabPlayers[i].pipefd[0]);   // Fermeture du côté lecture du pipe
        close(tabPlayers[i].pipefd[1]);  // Fermeture du côté écriture du pipe
    }

    if (lines != NULL) {
        for (size_t i = 0; lines[i] != NULL; ++i) {
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