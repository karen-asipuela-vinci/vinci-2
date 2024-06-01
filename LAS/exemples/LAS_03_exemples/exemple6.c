#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "utils_v1.h"

int main(int argc, char **argv)
{
  // 1/ Création du pipe
  // Un pipe est créé : c'est un moyen de communication entre deux processus
  // 'pipefd' est un tableau de deux entiers : pipefd[0] est le descripteur de lecture
  // et pipefd[1] est le descripteur d'écriture
  int pipefd[2];
  int ret = pipe(pipefd);
  // En cas d'erreur, pipe renvoie -1
  checkNeg(ret, "pipe error");

  // 2/ Création de l'enfant
  // Un processus enfant est créé par sfork() (version sécurisée de fork())
  int childId = sfork();

  // PARENT
  if (childId > 0)
  {
    // 3/ Cloture du descripteur pour la lecture sur le pipe
    // Le processus parent n'a pas besoin de lire dans le pipe ([0]) :
    // l'extrémité de lecture du pipe est fermée
    ret = close(pipefd[0]);
    checkNeg(ret, "close error");

    // 4/ On écrit un entier pour le fils
    // On écrit un entier dans le pipe ([1])
    int intVal = 7;
    int nbChar = write(pipefd[1], &intVal, sizeof(int));
    checkCond(nbChar != sizeof(int), "write error");

    // 5/ On clôture le côté écriture du pipe
    // Le processus parent n'a plus besoin d'écrire dans le pipe ([1]) :
    ret = close(pipefd[1]);
    checkNeg(ret, "close error");
  }
  // FILS
  else
  {
    // 3/ Cloture du descripteur d'écriture sur le pipe
    // Le processus fils n'a pas besoin d'écrire dans le pipe ([1]), il ne fait que lire
    int ret = close(pipefd[1]);
    checkNeg(ret, "close error");

    // 4/ On attend un entier de la part du père
    int intVal;
    int nbChar = read(pipefd[0], &intVal, sizeof(int));
    checkCond(nbChar != sizeof(int), "read error");

    printf("entier reçu de mon père: %i\n", intVal);

    // 5/ On clôture le côté lecture du pipe
    ret = close(pipefd[0]);
    checkNeg(ret, "close error");
  }
}
