/* Blocage de signal (sigprocmask) avant création du processus fils, 
   suivi de l'armement du signal (sigaction) et du déblocage du signal 
   (sigprocmask) dans le processus fils */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "utils_v1.h"

//***************************************************************************
// SIGUSR1 handler (fils)
//***************************************************************************

static const char *const HELLO = "Hello. Je suis le sigusr1_handler\n";

volatile sig_atomic_t end = 0;

void sigusr1_handler (int sig) {
  write(1, HELLO, strlen(HELLO));
  
  end = 1;
}

//***************************************************************************
// CHILD CODE
//***************************************************************************

void child_handler () {
  // armement du signal SIGUSR1
  ssigaction(SIGUSR1, sigusr1_handler);

  // déblocage du signal SIGUSR1
  // à l'aide d'un ensemble (masque) contenant uniquement SIGUSR1
  sigset_t set;
  ssigemptyset (&set);
  sigaddset(&set, SIGUSR1);
  ssigprocmask(SIG_UNBLOCK, &set, NULL);

  /* PROCESSUS ENFANT */
  pid_t ppid = getppid();
  printf("Je suis le fils de PID %d\n", ppid);
  while (!end) {
    sleep(1);
  }
}

//***************************************************************************
// MAIN
//***************************************************************************

int main () {
  // blocage du signal SIGUSR1
  // à l'aide d'un ensemble (masque) contenant uniquement SIGUSR1
  sigset_t set;
  ssigemptyset(&set);
  sigaddset(&set, SIGUSR1);
  ssigprocmask(SIG_BLOCK, &set, NULL);

  pid_t childId = fork_and_run0(child_handler);

  /* PROCESSUS PARENT */
  printf("Je suis le pere de PID %d. ", childId);
  printf("J'envoie un signal SIGUSR1 à mon fils\n");
  skill(childId, SIGUSR1);

  int statut;
  swaitpid(childId, &statut,0);
  printf("Mon fils %d s'est terminé avec le statut: %d\n", childId, WEXITSTATUS(statut));
}
