/* Risque lié à un armement de signal (sigaction) dans le processus fils */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "utils_v1.h"

//***************************************************************************
// SIGUSR1 handler (fils)
//***************************************************************************

// Message à afficher lors de la réception du signal SIGUSR1
static const char *const HELLO = "Hello. Je suis le sigusr1_handler\n";

// Variable globale pour indiquer la fin du processus
volatile sig_atomic_t end = 0;

// Fonction pour gérer le signal SIGUSR1
void sigusr1_handler(int sig)
{
  // Écrit le message HELLO sur la sortie standard
  write(1, HELLO, strlen(HELLO));

  // Met fin au processus
  end = 1;
}

//***************************************************************************
// CHILD CODE
//***************************************************************************

// Fonction exécutée par le processus fils
void child_handler()
{
  // Arme le signal SIGUSR1 pour appeler sigusr1_handler lors de sa réception
  ssigaction(SIGUSR1, sigusr1_handler);

  /* PROCESSUS ENFANT */
  // Obtient le PID du processus parent
  pid_t ppid = getppid();
  // Affiche le PID du processus parent
  printf("Je suis le fils de PID %d\n", ppid);
  // Boucle jusqu'à ce que le signal SIGUSR1 soit reçu
  while (!end)
  {
    sleep(1);
  }
}

//***************************************************************************
// MAIN
//***************************************************************************

// Fonction principale
int main()
{
  // Crée un processus fils et exécute child_handler
  pid_t childId = fork_and_run0(child_handler);

  /* PROCESSUS PARENT */
  // Affiche le PID du processus fils
  printf("Je suis le pere de PID %d. ", childId);
  // Envoie le signal SIGUSR1 au processus fils
  printf("J'envoie un signal SIGUSR1 à mon fils\n");
  skill(childId, SIGUSR1);

  // Attends la fin du processus fils
  int statut;
  swaitpid(childId, &statut, 0);
  // Affiche le statut de fin du processus fils
  printf("Mon fils %d s'est terminé avec le statut: %d\n", childId, WEXITSTATUS(statut));
}