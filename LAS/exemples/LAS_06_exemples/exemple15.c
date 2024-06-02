#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#include "utils_v2.h"

#define KEY 369
#define PERM 0666 // droits d'accès, classiques

/******************************************************************************
// CHILD HANDLER
// ******************************************************************************/
void child_handler () {
  // CREATE SHARED MEMORY
  // quand on créer une ressource -> définir droits d'accès
  int shm_id = sshmget(KEY, sizeof(int), IPC_CREAT | PERM);
  int* z = sshmat(shm_id); // = pointeur vers la mémoire partagée

  printf("IN CHILD: shared mem value: *z = %d\n", *z);
  // on modifie la valeur de la mémoire partagée
  *z = 987654321;
  // puis on la détache/supprime
  sshmdt(z);
}

//******************************************************************************
//MAIN FUNCTION
//******************************************************************************
int main (int argc, char *argv[]) {
  pid_t cpid = fork_and_run0(&child_handler);
  
  swaitpid(cpid, NULL, 0);  // make sure child finishes before accessing shared memory
  
  // GET SHARED MEMORY 
  int shm_id = sshmget(KEY, sizeof(int), 0);
  int* z = sshmat(shm_id);
  
  printf("IN PARENT: shared mem value: *z = %d\n", *z);
  
  sshmdt(z);

  //COMMENT OR UNCOMMENT
  sshmdelete(shm_id);
}




 