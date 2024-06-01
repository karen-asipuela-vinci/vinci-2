#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "ipc_conf.h"
#include "utils_v2.h"


//******************************************************************************
// MAIN FUNCTION
//******************************************************************************
int main (int argc, char *argv[]) {  
  int id = sshmget(RADAR_KEY, sizeof(int), IPC_CREAT | PERM);
  int* v = sshmat(id);

  int i = 0;
  while(i != 12) {
    i++;
    printf("%d => %d\n", i, *v);
    sleep(5);
  }

  sshmdt(v);
  //sshmdelete(id);  // radar a la responsabilité de détruire la shm
}
