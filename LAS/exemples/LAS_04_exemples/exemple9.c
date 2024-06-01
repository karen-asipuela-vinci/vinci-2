/* Envoi d'un signal SUGUSR1 du processus père à son fils */
/*
SIGUSR1 est un signal spécifique à l'utilisateur dans les systèmes d'exploitation de type Unix, comme Linux.
Il n'a pas de comportement par défaut associé et est destiné à être utilisé dans les programmes d'utilisateur.
Il peut être utilisé pour n'importe quel but et est généralement utilisé pour informer un processus parent
que son processus enfant est prêt pour le traitement ou pour informer un processus enfant qu'il doit se terminer.
Dans le code que vous avez fourni, SIGUSR1 est utilisé pour signaler au processus enfant qu'il doit terminer son exécution.
*/

// ! comprendre mais appliquer le code de exemple10.c

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include "utils_v1.h"

//***************************************************************************
// * SIGUSR1 handler (fils)
//***************************************************************************

static const char *const HELLO = "Hello, je suis le sigusr1_handler\n";

// déclaration d'une variable volatile pour indiquer la fin du programme
// elle permet de savoir si le signal SIGUSR1 a été reçu
// volatile = variable qui peut être modifiée par un signal
volatile sig_atomic_t end = 0;

// déclaration d'un gestionnaire de signal (sigusr1)
void sigusr1_handler(int sig)
{
  // écriture d'un message dans la sortie standard
  // besoin de connaître la taille de la chaîne de caractères
  const size_t sz = strlen(HELLO); // async-signal-safe function
  // ! write dans 1 (sortie standard)
  write(1, HELLO, sz); // async-signal-safe function

  end = 1;
}

//***************************************************************************
// CHILD CODE
//***************************************************************************

void child_handler()
{
  /* PROCESSUS ENFANT */
  pid_t pid = getpid();
  pid_t ppid = getppid();
  printf("Je suis le processus %d, fils de %d\n", pid, ppid);
  while (end == 0)
  {
    sleep(1);
  }
}

//***************************************************************************
// MAIN
//***************************************************************************

int main()
{
  // initialisation de la structure sigaction
  // sigaction est une structure qui permet de définir le comportement d'un signal
  struct sigaction action = {0};
  action.sa_handler = sigusr1_handler;

  // armement du signal SUGUSR1
  int ret = sigaction(SIGUSR1, &action, NULL);
  checkNeg(ret, "erreur sigaction 1");

  // création d'un processus fils
  pid_t childId = fork_and_run0(child_handler);

  /* PROCESSUS PARENT */
  pid_t pid = getpid();
  printf("Je suis le processus pere (PID %d). ", pid);
  printf("J'envoie un signal SIGUSR1 à mon fils (PID %d)\n", childId);

  // envoi du signal SIGUSR1 au processus fils
  ret = kill(childId, SIGUSR1);
  checkNeg(ret, "erreur kill SIGUSR1");

  // attente safe de la fin du processus fils
  // waitpid = attendre la fin d'un processus
  int statut;
  swaitpid(childId, &statut, 0);
  printf("Mon fils %d s'est terminé avec le statut: %d\n", childId, WEXITSTATUS(statut));
}
