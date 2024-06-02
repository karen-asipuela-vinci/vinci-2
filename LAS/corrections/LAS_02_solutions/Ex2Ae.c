#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char **argv)
{
    char *str1 = "trois .. deux .. un ..";
    char *str2 = "partez !";

    printf("%s", str1);
    fflush(stdout);

    /* Création du processus fils */
    int childId = fork();
    if (childId == -1)
    {
        perror("Fork failed");
        exit(20);
    }

    if (!childId)
    {
        /* Dans le processus enfant */
        printf("%s", str2);
    }
}

/*
Y-a-t-il une différence de comportement entre les deux versions ?
Si oui, expliquez pourquoi puis modifiez
ce qu’il faut pour régler le problème de la première version (sans \n).
*/