#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>

#include "utils_v1.h"

#define MAX_LINE_LENGTH 80

// Fonction pour écrire une ligne dans un fichier
void writeToFile(int fd, char* line) {
    if (write(fd, line, strlen(line)) == -1) { // Écriture de la ligne dans le fichier
        perror("Error writing to file");
        exit(1);
    }
    if (write(fd, "\n", 1) == -1) { // Écriture d'un saut de ligne dans le fichier
        perror("Error writing to file");
        exit(1);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) { // Vérification du nombre d'arguments passés au programme
        fprintf(stderr, "Usage: %s <file1> <file2>\n", argv[0]);
        exit(1);
    }

    char* file1 = argv[1]; // Nom du premier fichier
    char* file2 = argv[2]; // Nom du deuxième fichier

    //ouverture du fichier en écriture
    //si n'existe pas, le crée
    //si existe, le vide (O_TRUNC)
    int fd1 = open(file1, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd1 == -1) {
            perror("Error opening file");
            exit(1);
        }

    int fd2 = open(file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd2 == -1) {
            perror("Error opening file");
            exit(1);
        }

    // Tableau pour stocker une ligne de texte
    char line[MAX_LINE_LENGTH + 1];

    while (fgets(line, sizeof(line), stdin) != NULL) { // Lecture d'une ligne depuis l'entrée standard
    //on utilise fgets car ligne entière
        line[strcspn(line, "\n")] = '\0'; // Suppression du caractère de saut de ligne à la fin de la ligne

        // Vérification si la première lettre de la ligne est une lettre alphabétique
        if (isalpha(line[0])) {
            if (isupper(line[0])) { // Vérification si la première lettre est en majuscule
                writeToFile(fd1, line); // Écriture de la ligne dans le premier fichier
            } else { // Si la première lettre est en minuscule
                writeToFile(fd2, line); // Écriture de la ligne dans le deuxième fichier
            }
        }
    }

    close(fd1); // Fermeture du premier fichier
    close(fd2); // Fermeture du deuxième fichier
    return 0;
}
