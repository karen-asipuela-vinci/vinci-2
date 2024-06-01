/* Exemple de terminaison fautive du consommateur (lecteur) alors que
   le producteur (écrivain) écrit toujours sur le pipe. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "utils_v1.h"

void run(void *argv)
{
  // FILS
  // le descripteur de fichier est passé en paramètre
  int *pipefd = argv;

  // 3/ Cloture du descripteur d'écriture sur le pipe
  // Le processus fils n'a pas besoin d'écrire dans le pipe ([1]), il ne fait que lire
  int ret = close(pipefd[1]);
  checkNeg(ret, "close error");

  // 4/ On attend un entier de la part du père
  // Le processus fils lit un entier dans le pipe ([0])
  int intVal;
  int nbChar = read(pipefd[0], &intVal, sizeof(int));
  checkCond(nbChar != sizeof(int), "read error");

  printf("entier reçu de mon père: %i\n", intVal);

  // 5/ On clôture le côté lecture du pipe
  // Le processus fils n'a plus besoin de lire dans le pipe ([0]) :
  ret = close(pipefd[0]);
  checkNeg(ret, "close error");
}

int main(int argc, char **argv)
{
  // 1/ Création du pipe
  int pipefd[2];
  int ret = pipe(pipefd);
  checkNeg(ret, "pipe error");

  // 2/ Création de l'enfant
  // ici on utilise le retour de la fonction fork_and_run1,
  // qui est le pid du fils
  int child_pid = fork_and_run1(run, pipefd);
  printf("pid fils = %d\n", child_pid);

  // PARENT
  // 3/ Cloture du descripteur pour la lecture sur le pipe
  ret = close(pipefd[0]);
  checkNeg(ret, "close error");

  // 4/ On écrit un entier pour le fils
  int intVal = 7;
  int nbChar = write(pipefd[1], &intVal, sizeof(int));
  checkCond(nbChar != sizeof(int), "write error");

  // On attend la mort du fils
  int status;
  swaitpid(child_pid, &status, 0);

  printf("Le fils est mort\n");

  // 5/ On écrit à nouveau un entier alors que l'enfant n'est plus là
  printf("Là je devrais mourir car je vais parler à mon fils mort! \n");

  nbChar = write(pipefd[1], &intVal, sizeof(int)); // echo $? affiche 141 --> SIGPIPE
  checkCond(nbChar != sizeof(int), "write error"); // (cf. erreur EPIPE dans 'man 2 write')

  printf("I survived !\n");

  // 6/ On clôture le côté écriture du pipe
  ret = close(pipefd[1]);
  checkNeg(ret, "close error");
}
