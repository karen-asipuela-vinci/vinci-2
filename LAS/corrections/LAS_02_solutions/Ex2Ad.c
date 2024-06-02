#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char **argv)
{
    // char * car on ne modifie pas les chaînes de caractères
    // Sans \n:
    char *str1 = "trois .. deux .. un ..";
    char *str2 = "partez !";

    // Avec \n:
    // char *str1 = "trois .. deux .. un ..\n";
    // char *str2 = "partez !\n";

    printf("%s", str1);

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
Refaites les étapes b et c en remplaçant les appels système write
par l’appel à la fonction printf sans ‘\n’ dans les chaines.
Qu’affiche cette première version du programme lors de son exécution ?
Qu'affiche ce programme si les chaînes de caractères sont terminées par ‘\n’ ?
*/