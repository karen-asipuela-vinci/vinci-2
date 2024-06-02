#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#include "utils_v2.h"

#define KEY 369   // Clé unique pour identifier la mémoire partagée
#define PERM 0666 // Droits d'accès classiques pour la mémoire partagée

/******************************************************************************
// GESTIONNAIRE DE PROCESSUS ENFANT (Child handler)
// ******************************************************************************/
void child_handler()
{
  // CRÉATION DE LA MÉMOIRE PARTAGÉE
  // Lors de la création d'une ressource, il faut définir les droits d'accès
  int shm_id = sshmget(KEY, sizeof(int), IPC_CREAT | PERM); // Crée un segment de mémoire partagée
  int *z = sshmat(shm_id);                                  // Attache le segment de mémoire partagée à l'espace d'adressage du processus

  printf("DANS L'ENFANT : valeur de la mémoire partagée : *z = %d\n", *z);
  // Modification de la valeur de la mémoire partagée
  *z = 987654321;
  // Détachement et suppression de la mémoire partagée
  sshmdt(z);
}

//******************************************************************************
// FONCTION PRINCIPALE (main)
//******************************************************************************
int main(int argc, char *argv[])
{
  pid_t cpid = fork_and_run0(&child_handler); // Crée un processus enfant et exécute le gestionnaire d'enfant

  swaitpid(cpid, NULL, 0); // Assure que le processus enfant termine avant d'accéder à la mémoire partagée

  // ACCÈS À LA MÉMOIRE PARTAGÉE
  int shm_id = sshmget(KEY, sizeof(int), 0); // Accède au segment de mémoire partagée
  int *z = sshmat(shm_id);                   // Attache le segment de mémoire partagée à l'espace d'adressage du processus