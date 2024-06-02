#include <string.h>
#include <unistd.h>

#include "utils_v1.h"

//***************************************************************************
// CHILD CODE
//***************************************************************************

static const char *const SENTENCE = "signal SIGUSR1 reçu!\n";

volatile sig_atomic_t end = 0;

void sigur1handler()
{
  const size_t SZ = strlen(SENTENCE);
  write(1, SENTENCE, SZ);

  end = 1;
}

void childhandler()
{
  while (!end)
  {
    sleep(2);
  }
}

//***************************************************************************
// MAIN
//***************************************************************************

int main()
{
  ssigaction(SIGUSR1, sigur1handler);
  pid_t childID = fork_and_run0(childhandler);
  skill(childID, SIGUSR1);
}

/*
Modifiez votre programme pour que le père envoie le signal SIGUSR1 à son fils
et que le fils affiche le message « signal SIGUSR1 reçu ! » à la réception de
celui-ci, pour ensuite s’arrêter.

REMARQUES :
➢ Attention cette semaine, le signal doit être armé avant la création du fils.
Si ce n’est pas fait, le père risque d’envoyer le signal SIGUSR1 à son fils
avant que celui-ci n’ait eu le temps d’armer son handler, provoquant ainsi
la mort du fils. La semaine prochaine nous verrons une autre manière de faire.
➢ Attention également que la fonction printf n’est pas « signal-safe »
et ne peut donc pas être utilisée dans un gestionnaire de signal.
*/