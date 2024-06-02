#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../utils_v1.h"

#define BUFFER_SIZE 10 // Définit la taille du buffer de lecture

// Fonction pour vider le buffer d'entrée standard
void clearStdin()
{
    char c;
    int nbCharRd = read(0, &c, 1); // Lit un caractère de l'entrée standard
    while (nbCharRd == 1 && c != '\n')
    {                              // Tant qu'il y a des caractères à lire et que le caractère n'est pas une nouvelle ligne
        nbCharRd = read(0, &c, 1); // Continue à lire
    }
    checkNeg(nbCharRd, "Error reading stdin"); // Vérifie si la lecture a réussi
}

int main(int argc, char **argv)
{
    char bufRd[BUFFER_SIZE]; // Buffer de lecture

    printf("Introduisez votre ligne (max %d caractères): \n", BUFFER_SIZE); // Invite l'utilisateur à entrer une ligne

    int nbCharRd = read(0, bufRd, BUFFER_SIZE); // Lit l'entrée de l'utilisateur
    while (nbCharRd > 0)
    { // Tant qu'il y a des caractères à lire
        if (bufRd[nbCharRd - 1] == '\n')
        {                                                        // Si la ligne est terminée par une nouvelle ligne
            int res = write(1, bufRd, nbCharRd);                 // Écrit la ligne sur la sortie standard
            checkCond(res != nbCharRd, "error wrinting stdout"); // Vérifie si l'écriture a réussi
        }
        else
        {                                                                                     // Si la ligne est trop longue
            printf("Erreur: la ligne introduite fait plus de %d caractères.\n", BUFFER_SIZE); // Informe l'utilisateur que la ligne est trop longue
            clearStdin();                                                                     // Vide le buffer d'entrée standard
        }
        printf("Introduisez votre ligne (max %d caractères): \n", BUFFER_SIZE); // Invite à nouveau l'utilisateur à entrer une ligne
        nbCharRd = read(0, bufRd, BUFFER_SIZE);                                 // Lit à nouveau l'entrée de l'utilisateur
    }

    checkNeg(nbCharRd, "Error reading stdin"); // Vérifie si la lecture a réussi
}

/*

STDIN_FILENO is a macro defined in <unistd.h>.
At least for POSIX.1 compliant systems, it's required to be defined as 0.
Similarly, STDOUT_FILENO is 1 and STDERR_FILENO is 2.

From /usr/include/unistd.h

// Standard file descriptors.
#define STDIN_FILENO    0       // Standard input.
#define STDOUT_FILENO   1       // Standard output.
#define STDERR_FILENO   2       // Standard error output.

*/