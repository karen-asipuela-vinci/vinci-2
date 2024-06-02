#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "utils_v1.h"

// ! meilleure version que exo2Bb.c :
// ! utilise utils_v1.h
void childProcess()
{
    /* Dans le processus enfant */
    printf("4 5 6\n");
    exit(21);
}

int main(int argc, char **argv)
{
    /* Création du processus fils */
    int childId = fork_and_run0(childProcess);

    /* Dans le processus parent */

    // attente de la fin du fils
    int status;
    swaitpid(childId, &status, 0);

    printf("1 2 3\n");

    if (WIFEXITED(status))
    {
        int ec = WEXITSTATUS(status);
        printf("The exit status of the child with pid = %d is %d\n", childId, ec);
    }
    else
    {
        printf("Error: the child didn't terminate normally\n");
    }
}

/*
Réécrivez le programme précédent en utilisant la librairie utils (présente sur Moovin).
Celle-ci devrait vous faciliter la tâche et augmenter la clarté du code !
*/