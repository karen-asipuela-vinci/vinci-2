#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>

#include "utils_v1.h"

// CONSTANTE
#define DUREE_EXEC 5

// VARIABLES GLOBALES
volatile sig_atomic_t end = 0;
volatile sig_atomic_t nsigs_recus = 0;
volatile sig_atomic_t nsigs_envoyes = 0;

// DECLARATION DE FONCTIONS
void pere(pid_t);
void fils(); 
void incr_recu();
void fin_processus();
void fin_processus();

//***************************************************************************
// PROGRAMME PRINCIPAL
//***************************************************************************

int main () {  
   int res, status;
   pid_t pidfils;

   /* blocage du signal SIGUSR1 pour s'assurer qu'un 
      signal SIGUSR1 ne sera pas 'manqué' par le fils */
   sigset_t blocked;
   ssigemptyset(&blocked);
   ssigaddset(&blocked, SIGUSR1);
   ssigprocmask(SIG_BLOCK, &blocked, NULL);

   /* armement du signal SIGUSR1 */
   ssigaction(SIGUSR1, incr_recu);

   /* armement du signal SIGALRM */
   ssigaction(SIGALRM, fin_processus);

   /* armement du signal SIGUSR2 */
   ssigaction(SIGUSR2, fin_processus);

   switch (pidfils = fork()) {
   case -1:
      perror("fork");
      exit(2);
   case 0:   // FILS
      fils();
      exit(0);
   default:  // PERE
      pere(pidfils);
      swaitpid(pidfils, &status, 0);
      exit(0);
   }

   fprintf(stderr, "Sortie anormale du programme\n");
   exit(3);
}

//***************************************************************************
// PERE
//***************************************************************************

void pere (pid_t pidF) {
   /* définition d'un masque vide */
   sigset_t empty;
   ssigemptyset(&empty);
   
   /* programmation d'une alarme limitant la durée de l'exécution */
   printf("Durée de l'exécution limitée à %d secondes\n",DUREE_EXEC);
   alarm(DUREE_EXEC);

   while (end == 0) {
      /* envoi de SIGUSR1 au fils */
      skill(pidF, SIGUSR1);
      nsigs_envoyes++;

      /* mise en attente jusqu'à réception d'un signal */
      sigsuspend(&empty);
   }
   
   printf("%d/%d signaux envoyes/recus par pere\n",nsigs_envoyes, nsigs_recus);

   /* envoi de SIGUSR2 au fils */
   skill(pidF, SIGUSR2);
}

//***************************************************************************
// FILS
//***************************************************************************

void fils () {
   pid_t pidpere = getppid();

   /* définition d'un masque vide */
   sigset_t empty;
   ssigemptyset(&empty);
  
   while (end == 0) {
      /* mise en attente jusqu'à réception d'un signal */      
      sigsuspend(&empty);

      /* envoi de SIGUSR1 au père */
      skill(pidpere, SIGUSR1);
      nsigs_envoyes++;
   }
   
   printf("%d/%d signaux envoyes/recus par fils\n",nsigs_envoyes, nsigs_recus);
}

//***************************************************************************
// GESTIONNAIRES DE SIGNAUX
//***************************************************************************

// handler de SIGUSR1
void incr_recu () {
   nsigs_recus++;
}

// handler de SIGALRM et SIGUSR2
void fin_processus () {
   end = 1;
}


/* Analyse de la solution

 PROBLEME 1:
   L'action par défaut liée à la réception d'un signal est 
   généralement 'Terminate' (i.e. la terminaison du processus),
   ce qu'on veut éviter dans cet exercice.

   Modifier ce comportement en armant les signaux après avoir effectué 
   un fork() ne constitue pas une solution satisfaisante.  
   En effet, si le scheduler laisse la main au père après le fork,
   celui-ci enverra éventuellement un signal avant que son fils 
   aie eu le temps de l'armer. Dans ce cas, la réception du signal
   SIGUSR1 provoquera la terminaison du fils dès que le scheduler 
   lui passera la main.

 SOLUTION 1:
   L'armement des signaux avant fork() permet de s'assurer que 
   les signaux échangés entre les processus père et fils seront 
   traités par les gestionnaires de signaux.

 PROBLEME 2:
   Un autre risque avec les signaux est lié à leur caractère
   asynchrone: ils peuvent arriver n'importe quand (cela dépend
   notamment du scheduler). Il est donc parfaitement possible 
   que la réponse à un signal arrive entre l'envoi du signal 
   et le mise en attente de la réponse à l'aide de l'appel système
   pause [non vu dans ce cours, remplacé par sigsuspend] qui met 
   un processus en sommeil jusqu'à la réception d'un signal 
   quelconque (>< boucle d'attente active):
   
        kill(pid,SIGUSR1);
        // --> réception du signal de réponse (et exécution de son handler) 
        //     avant exécution de pause()
        pause();
        
   Dans ce cas, le processus restera indéfiniment
   en attente de la réponse qu'il a en fait déjà reçue!
   Voici un tel exemple d'exécution:

       $ ./ex5.2
       Durée de l'exécution limitée à 5 secondes
       1/0 signaux envoyes/recus par pere
       0/1 signaux envoyes/recus par fils

   En 5 secondes, ce programme devrait échanger plusieurs 
   centaines de milliers de signaux!

 SOLUTION 2:
   Pour éviter qu'un processus attende indéfiniment un signal
   qu'il a déjà reçu, il faut contrôler quand le signal sera délivré
   au processus. Pour cela, un masque de processus est défini avant fork() 
   grâce à l'appel système sigprocmask afin que les signaux SIGUSR1 
   soient bloqués. De cette manière, même si un signal est reçu, 
   il restera en attente ('pending') jusqu'à ce qu'on le débloque. 
   Cela se fera de manière sure avec sigsuspend(), qui permet de se 
   mettre en attente d'un signal ou de le débloquer s'il était 'pending'
   (remarquez que pause() ne permet pas de débloquer un signal bloqué!).
   
 */