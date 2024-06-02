#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#include "utils_v2.h"

#define SHM_KEY 248
#define SEM_KEY 369
#define PERM 0666

#define Z_VALUE 97
#define NBR_CHILD_LOOP  50000
#define NBR_PARENT_LOOP 10000

//******************************************************************************
//CHILD HANDLER
//******************************************************************************
void child_handler () {
  // GET SEMAPHORE
  int sem_id = sem_get(SEM_KEY, 1);
  // GET SHARED MEMORY
  int shm_id = sshmget(SHM_KEY, sizeof(int), 0);
  int* z = sshmat(shm_id);
  
  for (int i = 0; i != NBR_CHILD_LOOP; i++) {
    sem_down0(sem_id);
    // START OF CRITICAL SECTION
    if (*z == 0) {
      *z = Z_VALUE;
    } else {
      (*z)--;
    }
    // END OF CRITICAL SECTION
    sem_up0(sem_id);
  }
  sshmdt(z);
}

//******************************************************************************
//MAIN FUNCTION
//******************************************************************************
int main (int argc, char *argv[]) {
  // CREATE SEMAPHORE 
  // plus simple que 15 -> fonction déjà créée
  int sem_id = sem_create(SEM_KEY, 1, PERM, 1); // init semaphores before fork to avoid race conditions
  // CREATE SHARED MEMORY 
  int shm_id = sshmget(SHM_KEY, sizeof(int), IPC_CREAT | PERM);
  int* z = sshmat(shm_id);
  
  pid_t cpid = fork_and_run0(&child_handler);
  
  for (int i = 0; i != NBR_PARENT_LOOP; i++) {
    sem_down0(sem_id);
    // START OF CRITICAL SECTION
    printf("IN PARENT: Shared memory value: *z = %d\n", *z);
    // END OF CRITICAL SECTION
    sem_up0(sem_id);
  }
  
  sshmdt(z);

  swaitpid(cpid, NULL, 0);  // make sure child finishes before removing semaphores
  
  // COMMENT OR UNCOMMENT
  //sshmdelete(shm_id);
  //sem_delete(sem_id);
}