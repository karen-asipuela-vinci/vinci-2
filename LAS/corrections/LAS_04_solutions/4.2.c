#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "utils_v1.h"

//***************************************************************************
// SIGNAL HANDLER
//***************************************************************************

void handler(int sig)
{
   char *msg = " Signal '";
   write(1, msg, strlen(msg));
   msg = strsignal(sig); // nécessite l'option: -D_DEFAULT_SOURCE
   write(1, msg, strlen(msg));
   msg = "' reçu ";
   write(1, msg, strlen(msg));
}

//***************************************************************************
// MAIN
//***************************************************************************

int main()
{
   /* afficher pid */
   pid_t pid = getpid();
   printf("[%d] Hello, I am TIMER!  ;)\n", pid);

   /* armement des 32 premiers signaux */
   struct sigaction action = {0};
   action.sa_handler = handler;
   for (int i = 0; i < 32; i++)
   {
      int res = sigaction(i, &action, NULL);
      if (res != 0)
      {
         // affichage des signaux qui ne peuvent
         // pas être armés (ex: SIGKILL, SIGSTOP)
         // cf. liste des signaux définis:  kill -l
         printf("Signal %d (%s) non capture\n", i, strsignal(i));
      }
   }
   printf("\n");

   char c = '.';
   while (1)
   {
      int res = write(1, &c, sizeof(char));
      if (res == -1 && errno != EINTR)
      { // code d’erreur EINTR = "Interrupted system call"
         perror("erreur: write\n");
         exit(1);
      }
      sleep(1);
   }
}

/*
Programme qui affiche le signal reçu
Ecrivez un programme « timer » qui, à la réception d’un signal,
affichera simplement le signal reçu avant de reprendre son traitement.
Pour afficher le signal reçu, utilisez la fonction strsignal(int sig)
définie dans <string.h> et ajoutez -D_DEFAULT_SOURCE aux flags de compilation.

Limitez-vous aux signaux classiques, càd. les 32 premiers
(pour afficher la liste des signaux définis sur votre système,
tapez la commande kill -l) et affichez un message d’erreur si un signal n’a pas pu être armé.
Une fois les signaux armés, le traitement de votre programme se limitera
à une boucle infinie consistant en l’écriture d’un point suivi d’un sleep(1).
Affichez un message indiquant si une erreur autre que l’interruption par un
signal (errno!=EINTR) s’est produite pendant l’exécution du write.

Testez votre programme avec différents signaux (commande kill exécutée
depuis un autre terminal).

Essayez notamment d’arrêter le processus avec Ctrl-C et Ctrl-Z.
*/