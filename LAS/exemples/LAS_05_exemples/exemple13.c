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

// Fonction exécutée par le processus fils
void child_handler()
{
  // Arme le signal SIGUSR1 pour appeler sigusr1_handler lors de sa réception
  ssigaction(SIGUSR1, sigusr1_handler);

  // Débloque le signal SIGUSR1
  // Crée un ensemble de signaux (masque) contenant uniquement SIGUSR1
  sigset_t set;
  // Initialise l'ensemble de signaux à vide
  ssigemptyset(&set);
  // Ajoute SIGUSR1 à l'ensemble de signaux
  sigaddset(&set, SIGUSR1);
  // Débloque SIGUSR1
  ssigprocmask(SIG_UNBLOCK, &set, NULL);
}