#define MAX_PLAYERS 4
#define TIME_INSCRIPTION 30
#include "messages.h"
#include "player.h"
#include "score.h"


Player tabPlayers[MAX_PLAYERS];
volatile sig_atomic_t end_inscriptions = 0;

void endServerHandler(int sig)
{
	end_inscriptions = 1;
}

int main(int argc, char const *argv[])
{
    int sockfd, newsockfd, i;
	StructMessage msg;
	int ret;
	struct pollfd fds[MAX_PLAYERS];
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
    int fd = fileno(file);
    char **lines = readFileToTable(fd);
    fclose(file);
    }

	ssigaction(SIGALRM, endServerHandler);
	ssigaction(SIGINT, endServerHandler);

	sockfd = initSocketServer(SERVER_PORT);
	printf("Le serveur tourne sur le port : %i \n", SERVER_PORT);

    //initialisation de la mémoire partagée
    Ranking* scores = initializeSharedMemory();
    int sem = initializeSemaphores();

    i = 0;
	int nbPLayers = 0;

	// INSCRIPTION PART
    //TODO
	alarm(TIME_INSCRIPTION);






    //END OF INSCRIPTION PART
    //CHECK IF ENOUGH PLAYERS REGISTERED
    printf("FIN DES INSCRIPTIONS\n");
	if (nbPLayers != MAX_PLAYERS)
	{
		printf("PARTIE ANNULEE .. PAS ASSEZ DE JOUEURS\n");
		msg.code = CANCEL_GAME;
		for (i = 0; i < nbPLayers; i++)
		{
			swrite(tabPlayers[i].sockfd, &msg, sizeof(msg));
		}
		disconnect_players(tabPlayers, nbPLayers);
		sclose(sockfd);
		exit(0);
	}

    //GAME PART
	int nbPlayersAlreadyPlayed = 0;
    int nbTurnsPlayed = 0;
    int currentTuile;
    int tuiles = initializeTiles();
   
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

        for (i = 0; i < nbPLayers; i++){
            swrite(tabPlayers[i].sockfd, &msg, sizeof(msg));
        }

        //TODO polls
    }

    //END OF GAME PART
    msg.code = FINISH_GAME;
      for (i = 0; i < nbPLayers; i++){
            swrite(tabPlayers[i].sockfd, &msg, sizeof(msg));
        }

    //TODO RECUPERER LES SCORES ENVOYES PAR LES JOUEURS

    //TRI DES SCORES 
    

    // liberation des différentes ressources a la fin du programme

    if (lines != NULL) {
        for (size_t i = 0; lines[i] != NULL; ++i) {
            free(lines[i]); 
        }
        free(lines); 
    }

    disconnect_players(tabPlayers, nbPLayers);
	sclose(sockfd);

    return 0;
}