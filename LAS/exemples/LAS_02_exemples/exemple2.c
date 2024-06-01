/// version utilisant les fonctions "check..." du module utils

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
  int childId = fork();
  checkCond(childId == -1, "Fork failed");

  if (childId != 0)   // childId = pid de l’enfant
  {
    /* Dans le processus parent */
    printf("Processus parent (pid=%i) en attente de la fin de son enfant (pid fils=%i).\n",getpid(),childId);

    /* Attente de la terminaison du processus fils */
    int status;   // statut de l’enfant terminé
    int waitId = waitpid(childId, &status, 0);   // waitId = pid renvoyé par le wait (=childId)
    checkCond(waitId == -1, "Wait error");
    
    printf("Processus parent se termine après son enfant (pid fils=%i).\n",childId);
  } 
  else 
  { 
    /* Dans le processus fils */
    printf("Je suis le fils '%s': pid=%i - ppid=%i\n",argv[0],getpid(),getppid());
    execl("./myScript.sh","myScript.sh", NULL);
    checkCond(true, "Exec failed");
  }
}