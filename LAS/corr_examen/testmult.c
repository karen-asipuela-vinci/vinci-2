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
void sigalrm_handler()
{
}

// TODO
void childHandler(void *questPipeArg, void *respPipeArg)
{
    char response[SIZE_REP];
    int responseInt;
    struct mult multiplication;
    int nbChar;
    int ret;

    int *questPipe = questPipeArg;
    int *respPipe = respPipeArg;

    sclose(respPipe[0]);
    sclose(questPipe[1]);

    while ((nbChar = sread(questPipe[0], &multiplication, sizeof(multiplication))))
    {
        printf("%d * %d = ", multiplication.a, multiplication.b);
        ret = readLimitedLine(response, SIZE_REP);
        if (ret == -1)
        {
            printf("\nle fils arrête\n");
            sclose(respPipe[1]);
            sclose(questPipe[0]);
            exit(25);
        }
        responseInt = atoi(response);
        ret = swrite(respPipe[1], &responseInt, sizeof(int));
    }
    sclose(respPipe[1]);
    sclose(questPipe[0]);
}

int main(int argc, char **argv)
{

    // TODO
    int questPipe[2]; /*father ---> child*/
    int respPipe[2];  /*child  ---> father*/
    struct mult multiplication;
    char response[SIZE_REP];
    int nbChar;
    int repOk = 0;
    int repKo = 0;
    int timer;
    int pidChild;

    srand(time(NULL));
    if (argc != 2)
    {
        fprintf(stderr, " Usage : %s sec\n", argv[0]);
        exit(1);
    }

    timer = atoi(argv[1]);

    spipe(questPipe);
    spipe(respPipe);

    pidChild = fork_and_run2(childHandler, questPipe, respPipe);

    int reponse;
    int reponseRecue;
    int i;
    int timeOver = 0;

    sclose(respPipe[1]);
    sclose(questPipe[0]);

    ssigaction(SIGALRM, sigalrm_handler);

    alarm(timer);

    for (i = 0; i < NB_QUEST; i++)
    {
        multiplication.a = alea();
        multiplication.b = alea();
        reponse = multiplication.a * multiplication.b;

        swrite(questPipe[1], &multiplication, sizeof(multiplication));

        /* reception de la réponse, validation et comptabilisation des bonnes et mauvaises réponses */
        nbChar = read(respPipe[0], &reponseRecue, sizeof(int));
        printf("\nréponse recue fils : %d \n", reponseRecue);
        if (nbChar == -1)
        {
            if (errno == EINTR)
            {
                // temps global écoulé -> on tue le fils
                timeOver = 1;
                skill(pidChild, SIGTERM);
                break;
            }
        }
        // CTRL-D
        if (nbChar == 0)
        {
            break;
        }
        if (reponseRecue == reponse)
            repOk++;
        else
            repKo++;

        reponseRecue = -1;
    }

    sclose(questPipe[1]);
    sclose(respPipe[0]);

    swaitpid(pidChild, NULL, 0);
    printf("\nFils a obtenu %d bonne(s) reponse(s), %d mauvaise(s)\n", repOk, repKo);
    if (timeOver == 1)
        printf("Temps imparti écoulé\n");
}
