/* Programme illustrant la perte de signaux */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include "utils_v1.h"

#define NBR 10000

//***************************************************************************
// signal handlers (fils)
//***************************************************************************

volatile sig_atomic_t cpt = 0;
volatile sig_atomic_t end = 0;

void sigusr1_handler (int sig) {
  cpt++;
}

void sigusr2_handler (int sig) {
  end = 1;
}

//***************************************************************************
// CHILD CODE
//***************************************************************************

void child_handler () {
  /* PROCESSUS ENFANT */
  while (end == 0) {
    sleep(1);
  }
  printf("Le fils a traité %d signaux SIGUSR1\n", cpt);
}

//***************************************************************************
// MAIN
//***************************************************************************

int main () {
  // armement des signaux SUGUSR1 et SIGUSR2
  ssigaction(SIGUSR1, sigusr1_handler);
  ssigaction(SIGUSR2, sigusr2_handler);

  pid_t childId = fork_and_run0(child_handler);

  /* PROCESSUS PARENT */
  // envoi de signaux SIGUSR1 au fils
  printf("Le père envoie %d signaux SIGUSR1 à son fils\n", NBR);
  for (int i=0; i!=NBR; i++) {
    skill(childId, SIGUSR1);
  }

  // envoi d'un signal SIGUSR2 pour terminer le fils
  skill(childId, SIGUSR2);
  
  int statut;
  swait(&statut);
}
