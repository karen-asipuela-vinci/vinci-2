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
  // Création d'un processus fils
  int childId = fork();                    // fork() crée un nouveau processus en dupliquant le processus existant
  checkCond(childId == -1, "Fork failed"); // Vérifie si la création du processus a échoué

  if (childId != 0) // Si childId est différent de 0, nous sommes dans le processus parent
  {
    // Affiche l'ID du processus parent et de l'enfant
    printf("Processus parent (pid=%i) en attente de la fin de son enfant (pid fils=%i).\n", getpid(), childId);

    // Attente de la terminaison du processus fils
    int status;                                // statut de l’enfant terminé
    int waitId = waitpid(childId, &status, 0); // waitpid() attend que le processus spécifié par childId se termine
    checkCond(waitId == -1, "Wait error");     // Vérifie si l'attente a échoué

    // Affiche un message indiquant que le processus parent se termine après son enfant
    printf("Processus parent se termine après son enfant (pid fils=%i).\n", childId);
  }
  else
  {
    // Si childId est égal à 0, nous sommes dans le processus fils
    printf("Je suis le fils '%s': pid=%i - ppid=%i\n", argv[0], getpid(), getppid()); // Affiche l'ID du processus fils et de son parent

    execl("./myScript.sh", "myScript.sh", NULL); // execl() remplace le processus fils actuel par un nouveau processus
    checkCond(true, "Exec failed");              // Vérifie si la création du nouveau processus a échoué
  }
}