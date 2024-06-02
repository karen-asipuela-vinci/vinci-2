#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char **argv)
{
    char *str1 = "Bonjour, "; // Déclaration et initialisation de la chaîne 'str1'
    char *str2 = "monde !\n"; // Déclaration et initialisation de la chaîne 'str2'

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
Ajoutez ‘\n’ à la fin des deux chaînes de caractères.
Qu’affiche ce programme modifié ?
*/