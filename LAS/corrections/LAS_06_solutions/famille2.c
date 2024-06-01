#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ipc_conf.h"
#include "utils_v2.h"


//******************************************************************************
// STATIC FUNCTION
//******************************************************************************
void childhandler(void* arg) {
  int sid = *(int*)arg;
  
  sem_down0(sid);
  /*** début de section critique ***/
  pid_t id = getpid();
  int i = 0;
  printf("je suis le fils %d\n", id);
  while(i != 2) {
    sleep(1);
    printf("je suis le fils %d\n", id);
    i++;
  }
  /*** fin de section critique ***/
  sem_up0(sid);
}

//******************************************************************************
// MAIN FUNCTION
//******************************************************************************
int main (int argc, char *argv[]) {
  int sid = sem_create(FAMILLE_KEY, 1, PERM, 1);
  
  fork_and_run1(childhandler, &sid);
  fork_and_run1(childhandler, &sid);
  
  swait(NULL);
  swait(NULL);
  
  //sem_delete(sid);
}