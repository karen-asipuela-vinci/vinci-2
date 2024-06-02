#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#include "utils_v2.h"

#define SHM_KEY 248 // Clé unique pour identifier la mémoire partagée
#define SEM_KEY 369 // Clé unique pour identifier le sémaphore
#define PERM 0666   // Droits d'accès classiques pour la mémoire partagée et le sémaphore

#define Z_VALUE 97            // Valeur initiale de la mémoire partagée
#define NBR_CHILD_LOOP 50000  // Nombre de boucles dans le processus enfant
#define NBR_PARENT_LOOP 10000 // Nombre de boucles dans le processus parent

//******************************************************************************
// GESTIONNAIRE DE PROCESSUS ENFANT (Child handler)
//******************************************************************************
void child_handler()
{
  // OBTENIR LE SÉMAPHORE
  int sem_id = sem_get(SEM_KEY, 1);
  // OBTENIR LA MÉMOIRE PARTAGÉE
  // !on utilise la version safe dans utils_v2.h
  int shm_id = sshmget(SHM_KEY, sizeof(int), 0);
  int *z = sshmat(shm_id); // Attacher la mémoire partagée

  // Boucle pour modifier la mémoire partagée
  for (int i = 0; i != NBR_CHILD_LOOP; i++)
  {
    sem_down0(sem_id); // Prendre le sémaphore: on down le sémaphore pour éviter les conditions de course
    // DÉBUT DE LA SECTION CRITIQUE
    if (*z == 0)
    {
      *z = Z_VALUE;
    }
    else
    {
      (*z)--;
    }
    // FIN DE LA SECTION CRITIQUE
    sem_up0(sem_id); // Libérer le sémaphore
  }
  sshmdt(z); // Détacher la mémoire partagée
}

//******************************************************************************
// FONCTION PRINCIPALE (main)
//******************************************************************************
int main(int argc, char *argv[])
{
  // CRÉER LE SÉMAPHORE
  int sem_id = sem_create(SEM_KEY, 1, PERM, 1); // !Initialiser le sémaphore avant le fork pour éviter les conditions de course
  // CRÉER LA MÉMOIRE PARTAGÉE
  int shm_id = sshmget(SHM_KEY, sizeof(int), IPC_CREAT | PERM);
  int *z = sshmat(shm_id); // attache mémoire: fournit un pointeur qui peut être utilisé pour accéder à la mémoire partagée.

  pid_t cpid = fork_and_run0(&child_handler); // Créer un processus enfant et exécuter le gestionnaire d'enfant

  for (int i = 0; i != NBR_PARENT_LOOP; i++)
  {
    sem_down0(sem_id); // Prendre le sémaphore
    // DÉBUT DE LA SECTION CRITIQUE
    printf("DANS LE PARENT : valeur de la mémoire partagée : *z = %d\n", *z);
    // FIN DE LA SECTION CRITIQUE
    sem_up0(sem_id); // Libérer le sémaphore
  }

  sshmdt(z); // Détacher la mémoire partagée

  swaitpid(cpid, NULL, 0); // !Assure que le processus enfant termine avant de supprimer les sémaphores

  // COMMENTER OU DÉCOMMENTER
  // sshmdelete(shm_id); // Supprimer la mémoire partagée
  // sem_delete(sem_id); // Supprimer le sémaphore
}