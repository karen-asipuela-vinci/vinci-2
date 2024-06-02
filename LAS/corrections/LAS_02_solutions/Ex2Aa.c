#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char **argv)
{
    int a = 5; // Déclaration et initialisation de la variable 'a'

    /* Création du processus fils */
    int childId = fork(); // Création d'un nouveau processus
    if (childId == -1)
    {                          // Si la création du processus échoue
        perror("Fork failed"); // Affiche un message d'erreur
        exit(10);              // Quitte le programme avec un code d'erreur
    }

    printf("La variable childId vaut %d\n", childId); // Affiche la valeur de 'childId'

    if (childId)
    {
        /* Dans le processus parent */
        int b = 5 * a;                               // Déclaration et initialisation de la variable 'b' dans le processus parent
        printf("Parent : a = %d et b = %d\n", a, b); // Affiche les valeurs de 'a' et 'b' dans le processus parent
    }
    else
    {
        /* Dans le processus enfant */
        int b = 2 * a;                               // Déclaration et initialisation de la variable 'b' dans le processus enfant
        printf("Enfant : a = %d et b = %d\n", a, b); // Affiche les valeurs de 'a' et 'b' dans le processus enfant
    }
}

/*
Ecrivez un programme qui définit une variable « a » de type int
et l’initialise à 5 ; crée un processus enfant ; affiche la valeur de retour de l’appel système fork.
Ensuite, il définit dans l’enfant une nouvelle variable « b » de type int,
lui affecte la valeur de « a * 2 » puis affiche le contenu de a et de b ;
le parent définit une autre variable « b » de type int, lui affecte la valeur de « a * 5 »
puis affiche le contenu de a et de b. Pour cet exercice, l’affichage peut se faire avec printf.
Qu’affiche ce programme lors de son exécution ?
*/