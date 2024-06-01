/// version utilisant les versions "safe" des syscalls 
/// fournies dans le module utils (sfork, swaitpid, sexecl)

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "utils_v1.h"

int main(int argc, char **argv)
{
  /* Création d'un processus fils */
  int childId = sfork();

  if (childId != 0) 
  {
    /* Dans le processus parent */
    printf("Processus parent (pid=%i) en attente de la fin de son enfant (pid fils=%i).\n",getpid(),childId);

    /* Attente de la terminaison du processus fils */
    int status;
    swaitpid(childId, &status, 0);
    
    printf("Processus parent se termine après son enfant (pid fils=%i).\n",childId);
  }
  else
  {
    /* Dans le processus fils */
    printf("Je suis le fils '%s': pid=%i - ppid=%i\n", argv[0], getpid(), getppid());
    sexecl("./myScript.sh", "myScript.sh", NULL);
  }
}