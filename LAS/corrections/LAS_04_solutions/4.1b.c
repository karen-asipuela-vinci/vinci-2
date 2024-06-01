#include <string.h>
#include <unistd.h>

#include "utils_v1.h"

//***************************************************************************
// CHILD CODE
//***************************************************************************

static const char *const SENTENCE = "signal SIGUSR1 reçu!\n";

volatile sig_atomic_t end = 0;

void sigur1handler() {
  const size_t SZ = strlen(SENTENCE);
  write(1, SENTENCE, SZ);
  
  end = 1;
}

void childhandler() {
  while (!end) {
    sleep(2);
  }
}

//***************************************************************************
// MAIN
//***************************************************************************

int main() {
  ssigaction(SIGUSR1, sigur1handler);
  pid_t childID = fork_and_run0(childhandler);
  skill(childID, SIGUSR1);
}