#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char **argv)
{
    char *str1 = "trois .. deux .. un .."; // Déclaration et initialisation de la chaîne 'str1'
    char *str2 = "partez !";               // Déclaration et initialisation de la chaîne 'str2'

    /* Écriture de 'str1' sur la sortie standard */
    if (write(1, str1, strlen(str1)) == -1)
    {                           // Si l'écriture échoue
        perror("Write failed"); // Affiche un message d'erreur
        exit(10);               // Quitte le programme avec un code d'erreur
    }

    /* Création du processus fils */
    int childId = fork(); // Création d'un nouveau processus
    if (childId == -1)
    {                          // Si la création du processus échoue
        perror("Fork failed"); // Affiche un message d'erreur
        exit(20);              // Quitte le programme avec un code d'erreur
    }

    if (!childId)
    {
        /* Dans le processus enfant */
        /* Écriture de 'str2' sur la sortie standard */
        if ((write(1, str2, strlen(str2))) == -1)
        {                           // Si l'écriture échoue
            perror("Write failed"); // Affiche un message d'erreur
            exit(10);               // Quitte le programme avec un code d'erreur
        }
    }
}

/*
Ecrivez un programme qui affiche la chaîne de caractères "trois .. deux .. un .."
avant de créer un processus enfant qui affiche la chaîne de caractères "partez !".
Les écritures doivent se faire grâce à l’appel système write.
Qu’affiche ce programme lors de son exécution ?
*/