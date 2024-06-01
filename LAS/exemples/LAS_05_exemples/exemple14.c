/* Blocage de signal (sigprocmask) avant création du processus fils, 
   suivi de l'armement du signal (sigaction) dans le fils et 
   de sa mise en attente du signal (sigsuspend) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "utils_v1.h"

#define HEARTS 7

//***************************************************************************
// CHILD CODE
//***************************************************************************

void childhandler() {
  // armement du signal SIGUSR1
  ssigaction(SIGUSR1, ehandler);  // ehanlder: fonction qui ne fait rien (cf. module utils)

  // ensemble (masque) contenant tous les signaux sauf SIGUSR1
  sigset_t set;
  ssigfillset(&set);
  sigdelset(&set, SIGUSR1);
  
  for (int i = 0; i != HEARTS; i++) {
    // attente du signal SIGUSR1 
    // (seul SIGUSR1 peut provoquer la sortie de sigsuspend)
    sigsuspend(&set);
    printf("signal SIGUSR1 reçu !\n");
  }
}

//***************************************************************************
// SIGCHLD handler (parent)
//***************************************************************************

static volatile  sig_atomic_t end = 0;

void sigchldhandler() {
  end = 1;
}

//***************************************************************************
// MAIN
//***************************************************************************

int main() {
  // blocage des signaux SIGUSR1 et SIGCHLD
  // à l'aide d'un ensemble (masque) contenant SIGUSR1 et SIGCHLD
  sigset_t set;
  ssigemptyset(&set);
  sigaddset(&set, SIGUSR1);
  sigaddset(&set, SIGCHLD);
  ssigprocmask(SIG_BLOCK, &set, NULL);
  
  pid_t childID = fork_and_run0(childhandler);

  /* PROCESSUS PARENT */
  // armement du signal SIGCHLD
  ssigaction(SIGCHLD, sigchldhandler);

  // déblocage du signal SIGCHLD
  // à l'aide d'un ensemble (masque) contenant uniquement SIGUSR1
  ssigemptyset(&set);
  sigaddset(&set, SIGCHLD);
  ssigprocmask(SIG_UNBLOCK, &set, NULL);
 
  while (!end) {
    // envoi de signal SIGUSR1 au fils
    skill(childID, SIGUSR1);
    sleep(1);
  }
  printf("Fin du père\n");
}
