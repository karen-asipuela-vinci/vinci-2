/* version utilisant les fonctions ssigaction() et skill() du module utils */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include "utils_v1.h"

//***************************************************************************
// SIGUSR1 handler (fils)
//***************************************************************************

// Déclaration d'une chaîne constante pour le message à afficher lors de la réception du signal SIGUSR1
static const char *const HELLO = "Hello, je suis le sigusr1_handler\n";

// Déclaration d'une variable globale volatile pour indiquer la fin du processus
volatile sig_atomic_t end = 0;

// Fonction de gestion du signal SIGUSR1
void sigusr1_handler(int sig)
{
  // Calcul de la longueur du message à afficher
  const size_t sz = strlen(HELLO); // async-signal-safe function
  // Affichage du message
  write(1, HELLO, sz); // async-signal-safe function

  // Modification de la variable globale pour indiquer la fin du processus
  end = 1;
}

//***************************************************************************
// CHILD CODE
//***************************************************************************

// Fonction exécutée par le processus enfant
void child_handler()
{
  // Affichage de l'ID du processus et de l'ID du processus parent
  pid_t pid = getpid();
  pid_t ppid = getppid();
  printf("Je suis le processus %d, fils de %d\n", pid, ppid);
  // Boucle jusqu'à ce que le signal SIGUSR1 soit reçu
  while (end == 0)
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
  // Enregistrement du gestionnaire de signal pour SIGUSR1
  // seulement besoin du signal et de la fonction de gestion du signal
  // l'action etc est gérée par ssigaction
  ssigaction(SIGUSR1, sigusr1_handler);

  // Création d'un processus enfant qui exécute child_handler
  pid_t childId = fork_and_run0(child_handler);

  /* PROCESSUS PARENT */
  // Affichage de l'ID du processus parent et de l'ID du processus enfant
  pid_t pid = getpid();
  printf("Je suis le processus pere (PID %d). ", pid);
  printf("J'envoie un signal SIGUSR1 à mon fils (PID %d)\n", childId);

  // Envoi du signal SIGUSR1 au processus enfant
  // sembable à kill(childId, SIGUSR1); mais avec checkNeg
  skill(childId, SIGUSR1);

  // Attente de la fin du processus enfant et affichage de son statut de sortie
  int statut;
  swaitpid(childId, &statut, 0);
  printf("Mon fils %d s'est terminé avec le statut: %d\n", childId, WEXITSTATUS(statut));
}