#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include "testmult.h"
#include "utils_v1.h"

/* Return a random number between 1 and 9 */
int alea()
{
    int c = (int)((double)rand() / (RAND_MAX) * (10 - 1)) + 1;
    return c;
}

// TODO

volatile sig_atomic_t end = 0;

void clientHandler(void *questionArg, void *resArg)
{
    int ret;
    int nbChar;
    int *questionPipe = questionArg;
    int *responsePipe = resArg;
    char bufResponse[SIZE_REP];

    // pipe fils : besoin de lire[0]
    sclose(responsePipe[0]);
    sclose(questionPipe[1]);

    // check la réponse du fils
    // tant qu'il y a qqch à lire !!
    struct mult multiplication;
    while (nbChar = sread(questionPipe[0], &multiplication, sizeof(multiplication)))
    {
        // affichage question
        printf("%d x %d =", multiplication.a, multiplication.b);
        ret = readLimitedLine(bufResponse, SIZE_REP);
        if (ret == -1)
        {
            // on ferme tout
            printf("** fils arreté**\n");
            sclose(questionPipe[0]);
            sclose(responsePipe[1]);
            exit(25);
        }

        // response lue en string
        int responseInt = atoi(bufResponse);
        // écriture de la réponse
        ret = swrite(responsePipe[1], &responseInt, SIZE_REP);
        if (ret == -1)
        {
            printf("pas écrit");
            sclose(questionPipe[0]);
            sclose(responsePipe[1]);
            exit(25);
        }

        // fermeture d'office
        sclose(questionPipe[0]);
        sclose(responsePipe[1]);
    }
}

int initSocketServer(int port)
{
}

void sigint_handler()
{
    printf("Fin serveur - Affichage des clients\n");
    end = 1;
}

int main(int argc, char **argv)
{

    // TODO
    // création de pipe
    
}
