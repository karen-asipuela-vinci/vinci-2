#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>

#include "../utils_v1.h"

#define MAX 80 // Définit la taille maximale de la ligne à lire

// Vérifie que le nombre correct d'arguments a été passé à la fonction
void checkUsage(int argc, char *argv[])
{
  if (argc != 3) // Si le nombre d'arguments n'est pas égal à 3
  {
    printf("Usage: %s file1 file2\n", argv[0]); // Affiche l'usage correct
    exit(EXIT_FAILURE);                         // Quitte le programme avec une erreur
  }
}

int main(int argc, char **argv)
{
  checkUsage(argc, argv); // Vérifie l'usage

  char c;
  char bufRd[MAX + 1];    // Buffer pour la lecture
  int nbCharRd, nbCharWr; // Nombre de caractères lus et écrits
  bool lnc = false;       // Indique si la ligne est conforme ou non

  int fd, fd1, fd2;                                        // Descripteurs de fichiers
  fd1 = open(argv[1], O_WRONLY | O_TRUNC | O_CREAT, 0644); // Ouvre le premier fichier en écriture
  checkNeg(fd1, "Error OPEN");                             // Vérifie si l'ouverture a réussi
  fd2 = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, 0644); // Ouvre le deuxième fichier en écriture
  checkNeg(fd2, "Error OPEN");                             // Vérifie si l'ouverture a réussi

  // Boucle de lecture
  while ((nbCharRd = read(0, bufRd, MAX + 1)))
  {
    checkNeg(nbCharRd, "Error reading file"); // Vérifie si la lecture a réussi

    if (bufRd[nbCharRd - 1] == '\n') // Si la ligne ne dépasse pas MAX caractères
    {
      bufRd[nbCharRd] = '\0';     // Supprime le '\n'
      if (isupper(bufRd[0]))      // Si le premier caractère est une majuscule
        fd = fd1;                 // Utilise le premier descripteur de fichier
      else if (islower(bufRd[0])) // Si le premier caractère est une minuscule
        fd = fd2;                 // Utilise le deuxième descripteur de fichier
      else
        lnc = true; // Sinon, la ligne n'est pas conforme
      if (!lnc)     // Si la ligne est conforme
      {
        nbCharWr = write(fd, bufRd, nbCharRd);                 // Écrit la ligne dans le fichier
        checkCond(nbCharWr != nbCharRd, "Error writing file"); // Vérifie si l'écriture a réussi
      }
    }
    else // Si la ligne est trop longue
    {
      // Vide le buffer de lecture clavier
      while ((nbCharRd = read(0, &c, 1)) && (c != '\n'))
        checkNeg(nbCharRd, "Error reading stdin"); // Vérifie si la lecture a réussi
    }
  }

  checkNeg(close(fd1), "Error CLOSE"); // Ferme le premier fichier
  checkNeg(close(fd2), "Error CLOSE"); // Ferme le deuxième fichier
}