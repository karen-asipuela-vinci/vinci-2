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
  printf("Je suis le fils '%s': pid=%i - ppid=%i\n", "exemple4", getpid(), getppid());
  sexecl("./myScript.sh", "myScript.sh", NULL);
}

int main(int argc, char **argv)
{
  /* Création d'un processus fils */
  int childId = fork_and_run0(childProcess);

  /* Dans le processus parent */
  printf("Processus parent (pid=%i) en attente de la fin de son enfant (pid fils=%i).\n",getpid(),childId);

  /* Attente de la terminaison du processus fils */
  int status;
  swaitpid(childId, &status, 0);
  
  printf("Processus parent se termine après son enfant (pid fils=%i).\n",childId);
}