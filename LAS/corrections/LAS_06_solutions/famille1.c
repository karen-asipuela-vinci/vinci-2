#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "utils_v2.h"


//******************************************************************************
// STATIC FUNCTION
//******************************************************************************
void childhandler() {
  pid_t id = getpid();
  int i = 0;
  printf("je suis le fils %d\n", id);
  while(i != 2) {
    sleep(1);
    printf("je suis le fils %d\n", id);
    i++;
  }
}

//******************************************************************************
// MAIN FUNCTION
//******************************************************************************
int main (int argc, char *argv[]) {
  fork_and_run0(childhandler);
  fork_and_run0(childhandler);
  
  swait(NULL);
  swait(NULL);
}
