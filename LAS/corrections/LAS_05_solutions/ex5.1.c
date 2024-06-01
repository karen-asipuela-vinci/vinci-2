#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#include "utils_v1.h"

#define HEARTBEAT_TIME 3
#define ALERT_TIME 8
#define DOWN_CODE 5

/*******************/
/* SIGNAL HANDLERS */
/*******************/

void sigalrmChildHandler (int num) {
  // send heartbeat to father
  skill(getppid(), SIGUSR1);  
  // reset countdown
  alarm(HEARTBEAT_TIME);
}

void sigalrmParentHandler (int num) {
  const char* msg = "Erreur: Mon fils est down\n";
  nwrite(2, msg, strlen(msg));
  
  _exit(DOWN_CODE);
}

void sigusr1Handler (int sig) {
  const char* msg = "Mon fils est toujours en vie\n";
  nwrite(1, msg, strlen(msg));

  // reset countdown
  alarm(ALERT_TIME);
}

/*****************/
/* MAIN FUNCTION */
/*****************/

int main () {
  /* blocage des signaux SIGUSR1, SIGALRM et SIGINT */
  sigset_t blocked;
  ssigemptyset(&blocked);
  ssigaddset(&blocked, SIGUSR1);
  ssigaddset(&blocked, SIGALRM);
  ssigaddset(&blocked, SIGINT);
  ssigprocmask(SIG_BLOCK, &blocked, NULL);
  
  pid_t childID = fork();

  // PERE
  if (childID > 0) {
    /* armement des signaux SIGUSR1 et SIGALRM */
    ssigaction(SIGUSR1, sigusr1Handler);
    ssigaction(SIGALRM, sigalrmParentHandler);

    /* déblocage des signaux SIGUSR1 et SIGALRM, mais pas de SIGINT */
    ssigdelset(&blocked, SIGINT);
    ssigprocmask(SIG_UNBLOCK, &blocked, NULL);
  
    /* lancement d'un compte à rebour de 12 secondes */
    alarm(ALERT_TIME);

    while (true) {
      sleep(10);
    }
  }
  // FILS
  else {
    /* armement du signal SIGALRM */
    ssigaction(SIGALRM, sigalrmChildHandler);

    /* déblocage des signaux SIGUSR1, SIGALRM et SIGINT */
    ssigprocmask(SIG_UNBLOCK, &blocked, NULL);

    /* lancement d'un compte à rebour de  secondes */
    alarm(HEARTBEAT_TIME);
    
    while (true) {   
      sleep(10);
    }
  }
}

