#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "utils_v1.h"

#define HEARTS 7

//***************************************************************************
// SIGUSR1 (child)
//***************************************************************************

static const char *const SENTENCE = "signal SIGUSR1 reçu !\n";

volatile sig_atomic_t hearts = HEARTS;

void sigusr1handler()
{
  const size_t SZ = strlen(SENTENCE);
  write(1, SENTENCE, SZ);

  hearts--;

  if (hearts == 0)
  {
    _exit(0); // async-signal-safe function, unlike exit()
  }
}

//***************************************************************************
// SIGCHD (parent)
//***************************************************************************

volatile sig_atomic_t end = 0;

void sigchldhandler()
{
  end = 1;
}

//***************************************************************************
// CHILD CODE
//***************************************************************************

void childhandler()
{
  while (1)
  {
    sleep(2);
  }
}

//***************************************************************************
// MAIN
//***************************************************************************

int main()
{
  ssigaction(SIGUSR1, sigusr1handler);
  ssigaction(SIGCHLD, sigchldhandler);

  pid_t childID = fork_and_run0(childhandler);

  while (!end)
  {
    skill(childID, SIGUSR1);
    sleep(1);
  }
  printf("Fin du père\n");
}

/*
Processus « chat aux 7 vies » : modifiez votre code pour que le père envoie
toutes les secondes un signal SIGUSR1 à son fils.
Le fils ne devra se terminer que lorsqu'il aura reçu 7 fois le signal de son
père.

REMARQUES :
➢ Attention, des signaux peuvent être perdus. Le père devra donc peut-être
envoyer plus de 7 signaux à son fils.
➢Vous devez bien faire attention à ce que votre fils ne se termine pas avant la
réception des 7 signaux.
➢Notez que lorsque le fils est terminé, un signal SIGCHLD sera automatiquement
envoyé au père. Utilisez ce signal pour provoquer l’arrêt du processus père.
*/