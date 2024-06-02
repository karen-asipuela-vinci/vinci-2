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

void childhandler()
{
  // Arme le signal SIGUSR1 pour appeler ehandler lors de sa réception
  ssigaction(SIGUSR1, ehandler); // ehandler: fonction qui ne fait rien (cf. module utils)

  // Crée un ensemble de signaux (masque) contenant tous les signaux sauf SIGUSR1
  sigset_t set;
  ssigfillset(&set);
  sigdelset(&set, SIGUSR1);

  for (int i = 0; i != HEARTS; i++)
  {
    // Met le processus en attente jusqu'à la réception du signal SIGUSR1
    // (seul SIGUSR1 peut provoquer la sortie de sigsuspend)
    sigsuspend(&set);
    printf("signal SIGUSR1 reçu !\n");
  }
}

//***************************************************************************
// SIGCHLD handler (parent)
//***************************************************************************

// Variable globale pour indiquer la fin du processus
static volatile sig_atomic_t end = 0;

// Fonction pour gérer le signal SIGCHLD
void sigchldhandler()
{
  // Met fin au processus
  end = 1;
}

//***************************************************************************
// MAIN
//***************************************************************************

// Fonction principale
int main()
{
  // Bloque les signaux SIGUSR1 et SIGCHLD
  // Crée un ensemble de signaux (masque) contenant SIGUSR1 et SIGCHLD
  sigset_t set;
  ssigemptyset(&set);
  sigaddset(&set, SIGUSR1);
  sigaddset(&set, SIGCHLD);
  ssigprocmask(SIG_BLOCK, &set, NULL);

  // Crée un processus fils et exécute childhandler
  pid_t childID = fork_and_run0(childhandler);

  /* PROCESSUS PARENT */
  // Arme le signal SIGCHLD pour appeler sigchldhandler lors de sa réception
  ssigaction(SIGCHLD, sigchldhandler);

  // Débloque le signal SIGCHLD
  // Crée un ensemble de signaux (masque) contenant uniquement SIGCHLD
  ssigemptyset(&set);
  sigaddset(&set, SIGCHLD);
  ssigprocmask(SIG_UNBLOCK, &set, NULL);

  // Boucle jusqu'à la fin du processus
  while (!end)
  {
    // Envoie le signal SIGUSR1 au processus fils
    skill(childID, SIGUSR1);
    sleep(1);
  }
  printf("Fin du père\n");
}