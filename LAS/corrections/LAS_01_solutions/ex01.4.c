#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
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

// Variables globales pour la lecture
int idx = -1;     // Index du caractère actuel dans le buffer
int size = -1;    // Taille du buffer
char buffer[MAX]; // Buffer de lecture

// Lit un bloc de données dans le buffer
void readBlock()
{
  if (size != 0 && idx == size) // Si le buffer est vide ou si tous les caractères ont été lus
  {
    size = read(0, buffer, MAX);  // Lit un bloc de données
    checkNeg(size, "Error READ"); // Vérifie si la lecture a réussi
    idx = 0;                      // Réinitialise l'index
  }
}

// Vérifie si la fin du fichier a été atteinte
bool eof()
{
  readBlock();      // Lit un bloc de données
  return size == 0; // Retourne vrai si la taille du buffer est 0, c'est-à-dire si la fin du fichier a été atteinte
}

// Lit un caractère du buffer
char readChar()
{
  char res = buffer[idx]; // Récupère le caractère à l'index actuel
  idx++;                  // Incrémente l'index
  return res;             // Retourne le caractère
}

// Lit un préfixe de la ligne actuelle
void readPrefix(char *pref, int *lengthPref, int *lengthTot, int max)
{
  *lengthPref = 0; // Réinitialise la longueur du préfixe
  *lengthTot = 0;  // Réinitialise la longueur totale

  bool eol = false;      // Indique si la fin de la ligne a été atteinte
  while (!eof() && !eol) // Tant que la fin du fichier ou la fin de la ligne n'a pas été atteinte
  {
    char current = readChar(); // Lit le caractère actuel
    eol = current == '\n';     // Met à jour l'indicateur de fin de ligne
    (*lengthTot)++;            // Incrémente la longueur totale

    if (*lengthPref < max) // Si la longueur du préfixe est inférieure à max
    {
      pref[*lengthPref] = current; // Ajoute le caractère au préfixe
      (*lengthPref)++;             // Incrémente la longueur du préfixe
    }
  }
}

int main(int argc, char *argv[])
{
  checkUsage(argc, argv); // Vérifie l'usage

  int r; // Variable pour stocker les résultats des appels de fonction

  int fd1 = open(argv[1], O_WRONLY | O_TRUNC | O_CREAT, 0644); // Ouvre le premier fichier en écriture
  checkNeg(fd1, "Error OPEN");                                 // Vérifie si l'ouverture a réussi
  int fd2 = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, 0644); // Ouvre le deuxième fichier en écriture
  checkNeg(fd2, "Error OPEN");                                 // Vérifie si l'ouverture a réussi

  while (!eof()) // Tant que la fin du fichier n'a pas été atteinte
  {
    int tot;                            // Longueur totale de la ligne
    int pref;                           // Longueur du préfixe
    char line[MAX];                     // Ligne actuelle
    readPrefix(line, &pref, &tot, MAX); // Lit le préfixe de la ligne

    if (tot <= MAX && 'A' <= line[0] && line[0] <= 'Z') // Si la ligne ne dépasse pas MAX caractères et commence par une majuscule
    {
      r = write(fd1, line, pref);          // Écrit la ligne dans le premier fichier
      checkCond(r != pref, "Error WRITE"); // Vérifie si l'écriture a réussi
    }
    else if (tot <= MAX && 'a' <= line[0] && line[0] <= 'z') // Si la ligne ne dépasse pas MAX caractères et commence par une minuscule
    {
      r = write(fd2, line, pref);          // Écrit la ligne dans le deuxième fichier
      checkCond(r != pref, "Error WRITE"); // Vérifie si l'écriture a réussi
    }
  }

  r = close(fd1);             // Ferme le premier fichier
  checkNeg(r, "Error CLOSE"); // Vérifie si la fermeture a réussi
  r = close(fd2);             // Ferme le deuxième fichier
  checkNeg(r, "Error CLOSE"); // Vérifie si la fermeture a réussi
}