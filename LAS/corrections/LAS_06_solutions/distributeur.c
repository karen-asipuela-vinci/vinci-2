#include <stdlib.h>
#include <stdio.h>

#include "ipc_conf.h"
#include "utils_v2.h"


//******************************************************************************
// MAIN FUNCTION
//******************************************************************************
int main (int argc, char *argv[]) {
  int shid = sshmget(LLN_SHM_KEY, 2 * sizeof(int), 0);
  
  int* dist = sshmat(shid);  // 1er entier de la shm

  int sid = sem_get(LLN_SEM_KEY, 1);
  
  sem_down0(sid);
  /*** début de section critique ***/
  (*dist)++;
  printf("%d\n", *dist);
  /*** fin de section critique ***/
  sem_up0(sid);
  
  sshmdt(dist);
  
  exit(EXIT_SUCCESS);
}