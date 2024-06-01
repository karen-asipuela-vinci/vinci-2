#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include "ipc_conf.h"
#include "utils_v2.h"

//******************************************************************************
// MAIN FUNCTION
//******************************************************************************
int main (int argc, char *argv[]) {
  srand(time(NULL));
  
  int id = sshmget(RADAR_KEY, sizeof(int), IPC_CREAT | PERM);
  int* v = sshmat(id);

  int i = 0;
  while(i != 20) {
    i++;
    *v = rand();
    //printf("RADAR %d => %d\n", i, *v);
    sleep(3);
  }

  sshmdt(v);
  //sshmdelete(id);
}
