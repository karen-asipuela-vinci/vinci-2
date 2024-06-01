/// version utilisant une des fonctions fork_and_run()
/// fournies dans le module utils: fork_and_run0 sans paramètre ;
/// notez que argv[0] n'est plus directement accessible dans le processus fils
/// (implémenté par la fonction childProcess())

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "utils_v1.h"

void childProcess()
{
  /* Dans le processus fils */
  // Affiche l'ID du processus fils et de son parent
  printf("Je suis le fils '%s': pid=%i - ppid=%i\n", "exemple4", getpid(), getppid());

  // sexecl() est une version sécurisée de execl() qui termine le programme en cas d'échec
  // Remplace le processus fils actuel par un nouveau processus
  sexecl("./myScript.sh", "myScript.sh", NULL);
}

int main(int argc, char **argv)
{
  /* Création d'un processus fils */
  // fork_and_run0() crée un nouveau processus et exécute la fonction spécifiée dans le processus fils
  int childId = fork_and_run0(childProcess);

  /* Dans le processus parent */
  // Affiche l'ID du processus parent et de l'enfant
  printf("Processus parent (pid=%i) en attente de la fin de son enfant (pid fils=%i).\n", getpid(), childId);

  /* Attente de la terminaison du processus fils */
  // swaitpid() est une version sécurisée de waitpid() qui termine le programme en cas d'échec
  int status;
  swaitpid(childId, &status, 0);

  // Affiche un message indiquant que le processus parent se termine après son enfant
  printf("Processus parent se termine après son enfant (pid fils=%i).\n", childId);
}