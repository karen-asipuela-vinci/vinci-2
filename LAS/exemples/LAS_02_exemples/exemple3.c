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
  // sfork() est une version sécurisée de fork() qui termine le programme en cas d'échec
  int childId = sfork();

  if (childId != 0)
  {
    /* Dans le processus parent */
    // Affiche l'ID du processus parent et de l'enfant
    printf("Processus parent (pid=%i) en attente de la fin de son enfant (pid fils=%i).\n", getpid(), childId);

    /* Attente de la terminaison du processus fils */
    // swaitpid() est une version sécurisée de waitpid() qui termine le programme en cas d'échec
    // waitpid() attend que le processus spécifié par childId se termine
    int status;
    swaitpid(childId, &status, 0);

    // Affiche un message indiquant que le processus parent se termine après son enfant
    printf("Processus parent se termine après son enfant (pid fils=%i).\n", childId);
  }
  else
  {
    /* Dans le processus fils */
    // Affiche l'ID du processus fils et de son parent
    printf("Je suis le fils '%s': pid=%i - ppid=%i\n", argv[0], getpid(), getppid());

    // sexecl() est une version sécurisée de execl() qui termine le programme en cas d'échec
    // execl() remplace le processus fils actuel par un nouveau processus
    sexecl("./myScript.sh", "myScript.sh", NULL);
  }
}