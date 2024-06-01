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

void handler (int sig) {
   char* msg = " Signal '";
   write(1, msg, strlen(msg));
   msg = strsignal(sig);    // nécessite l'option: -D_DEFAULT_SOURCE
   write(1, msg, strlen(msg));
   msg = "' reçu ";
   write(1, msg, strlen(msg));
}


//***************************************************************************
// MAIN
//***************************************************************************

int main() {
   /* afficher pid */
   pid_t pid = getpid();
   printf("[%d] Hello, I am TIMER!  ;)\n", pid);

   /* armement des 32 premiers signaux */
   struct sigaction action = {0};
   action.sa_handler = handler;
   for (int i = 0; i < 32; i++) {
      int res = sigaction(i, &action, NULL);
      if (res != 0) {
         // affichage des signaux qui ne peuvent 
         // pas être armés (ex: SIGKILL, SIGSTOP)
         // cf. liste des signaux définis:  kill -l
         printf("Signal %d (%s) non capture\n", i, strsignal(i));  
      }
   }
   printf("\n");

   char c = '.';   
   while (1) {       
     int res = write(1,&c,sizeof(char));
     if (res == -1 && errno != EINTR) {  // code d’erreur EINTR = "Interrupted system call"
        perror("erreur: write\n");
        exit(1);
     }
     sleep(1);
   }
}
