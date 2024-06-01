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

// Déclaration de deux variables globales volatiles pour compter les signaux reçus et indiquer la fin du processus
volatile sig_atomic_t cpt = 0;
volatile sig_atomic_t end = 0;

// Gestionnaire de signal pour SIGUSR1
void sigusr1_handler(int sig)
{
  // Incrémentation du compteur de signaux reçus
  cpt++;
}

// Gestionnaire de signal pour SIGUSR2
void sigusr2_handler(int sig)
{
  // Modification de la variable globale pour indiquer la fin du processus
  end = 1;
}

//***************************************************************************
// CHILD CODE
//***************************************************************************

// Fonction exécutée par le processus enfant
void child_handler()
{
  /* PROCESSUS ENFANT */
  // Boucle jusqu'à ce que le signal SIGUSR2 soit reçu (variable end)
  while (end == 0)
  {
    sleep(1);
  }
  // Affichage du nombre de signaux SIGUSR1 traités (variable cpt)
  printf("Le fils a traité %d signaux SIGUSR1\n", cpt);
}

//***************************************************************************
// MAIN
//***************************************************************************

// Fonction principale
int main()
{
  // Enregistrement des gestionnaires de signal pour SIGUSR1 et SIGUSR2
  // avec ssigaction
  ssigaction(SIGUSR1, sigusr1_handler);
  ssigaction(SIGUSR2, sigusr2_handler);

  // Création d'un processus enfant qui exécute child_handler
  pid_t childId = fork_and_run0(child_handler);

  /* PROCESSUS PARENT */
  // Envoi de NBR signaux SIGUSR1 au processus enfant
  printf("Le père envoie %d signaux SIGUSR1 à son fils\n", NBR);
  for (int i = 0; i != NBR; i++)
  {
    skill(childId, SIGUSR1);
  }

  // Envoi d'un signal SIGUSR2 au processus enfant pour le terminer
  skill(childId, SIGUSR2);

  // Attente de la fin du processus enfant
  int statut;
  swait(&statut);
}