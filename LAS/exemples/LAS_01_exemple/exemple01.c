#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "utils_v1.h"

#define BUFFERSIZE 80 // Définition de la taille du buffer
/*
Un buffer est une zone de mémoire temporaire utilisée pour stocker des données pendant
leur transfert d'un endroit à un autre.
Le concept de buffer est utilisé dans de nombreux contextes en informatique,
notamment pour la lecture et l'écriture de fichiers,
le transfert de données sur le réseau, etc.

Dans le contexte de votre code, bufRd est un buffer utilisé pour lire des données de l'entrée
standard (le clavier, généralement) et les écrire dans un fichier.
La taille du buffer est définie par BUFFERSIZE, qui est défini comme 80.
Cela signifie que le programme lira jusqu'à 80 caractères à la fois de l'entrée standard
et les écrira dans le fichier. Si l'utilisateur tape plus de 80 caractères
avant d'appuyer sur Entrée, le programme lira et écrira les caractères en plusieurs fois.
*/
#define FILENAME "test" // Définition du nom du fichier

// Déclaration des fonctions
void writeFile(char *file);
void readFile(char *file);

int main(int argc, char **argv)
{
  writeFile(FILENAME); // Appel de la fonction writeFile
  readFile(FILENAME);  // Appel de la fonction readFile
}

void writeFile(char *file)
{
  char bufRd[BUFFERSIZE]; // Création du buffer

  // Ouverture du fichier en mode écriture
  int fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
  checkNeg(fd, "Error opening file");

  // Lecture de l'entrée standard, puis écriture dans le fichier jusqu'à EOF (Ctrl-D)
  char *msg = "Enter text lines (Ctrl-D to terminate):\n";
  int len = strlen(msg);
  int nbCharWr = write(1, msg, len);
  checkCond(nbCharWr != len, "Error writing on stdout");

  int nbCharRd = read(0, bufRd, BUFFERSIZE);
  while (nbCharRd > 0)
  {
    // Pour la première utilisation de la fonction "write",
    // nous supposons qu'elle est capable d'écrire "BUFFERSIZE" octets à la fois.
    // Attention, cette hypothèse est trop forte.
    // Nous allons corriger cela plus tard dans le cours.
    nbCharWr = write(fd, bufRd, nbCharRd);
    checkCond(nbCharWr != nbCharRd, "Error writing file");
    nbCharRd = read(0, bufRd, BUFFERSIZE);
  }

  checkNeg(nbCharRd, "Error reading stdin");

  // Fermeture du descripteur de fichier
  int res = close(fd);
  checkNeg(res, "Error closing fd");
}

void readFile(char *file)
{
  char bufRd[BUFFERSIZE]; // Création du buffer

  // Ouverture du fichier en mode lecture
  int fd = open(file, O_RDONLY);
  checkNeg(fd, "Error opening file");

  // Lecture du fichier, puis écriture sur STDOUT jusqu'à EOF
  int nbCharRd = read(fd, bufRd, BUFFERSIZE);
  while (nbCharRd > 0)
  {
    int nbCharWr = write(1, bufRd, nbCharRd);
    checkCond(nbCharWr != nbCharRd, "Error writing stdout");
    nbCharRd = read(fd, bufRd, BUFFERSIZE);
  }

  checkNeg(nbCharRd, "Error reading file");

  // Fermeture du descripteur de fichier
  int res = close(fd);
  checkNeg(res, "Error closing fd");
}