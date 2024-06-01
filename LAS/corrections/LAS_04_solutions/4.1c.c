#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "utils_v1.h"

#define HEARTS 7

//***************************************************************************
// SIGUSR1 (child)
//***************************************************************************

static const char *const SENTENCE = "signal SIGUSR1 reçu !\n";

volatile sig_atomic_t hearts = HEARTS;

void sigusr1handler() {
  const size_t SZ = strlen(SENTENCE);
  write(1, SENTENCE, SZ);
  
  hearts--;
  
  if (hearts == 0) {
    _exit(0);     // async-signal-safe function, unlike exit()
  }
}

//***************************************************************************
// SIGCHD (parent)
//***************************************************************************

volatile  sig_atomic_t end = 0;

void sigchldhandler() {
  end = 1;
}


//***************************************************************************
// CHILD CODE
//***************************************************************************

void childhandler() {
  while (1) {
    sleep(2);
  }
}

//***************************************************************************
// MAIN
//***************************************************************************

int main() {
  ssigaction(SIGUSR1, sigusr1handler);
  ssigaction(SIGCHLD, sigchldhandler);
  
  pid_t childID = fork_and_run0(childhandler);
  
  while (!end) {
    skill(childID, SIGUSR1);
    sleep(1);
  }
  printf("Fin du père\n");
}