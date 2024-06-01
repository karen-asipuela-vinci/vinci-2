/// version utilisant une des fonctions fork_and_run()
/// fournies dans le module utils: fork_and_run1 avec un paramètre ;
/// argv[0] est fourni en paramètre à la fonction childProcess()
/// (étant de type générique void*, il doit être casté en char*)

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "utils_v1.h"

void childProcess(void *name)
{
  /* Dans le processus fils */
  // Le paramètre 'name' est de type générique void*, il doit donc être casté en char*
  char *pgm = (char *)name;

  // Affiche l'ID du processus fils et de son parent
  printf("Je suis le fils '%s': pid=%i - ppid=%i\n", pgm, getpid(), getppid());

  // sexecl() est une version sécurisée de execl() qui termine le programme en cas d'échec
  // Remplace le processus fils actuel par un nouveau processus
  sexecl("./myScript.sh", "myScript.sh", NULL);
}

int main(int argc, char **argv)
{
  /* Création d'un processus fils */
  // fork_and_run1() crée un nouveau processus et exécute la fonction spécifiée dans le processus fils
  // Le deuxième paramètre de fork_and_run1() est passé à la fonction childProcess()
  int childId = fork_and_run1(childProcess, argv[0]);

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