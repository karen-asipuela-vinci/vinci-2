#include <stdio.h>
#include <unistd.h>

#include "inscriptionRequest.h"
#include "utils_v1.h"

static void child(void *arg1, void *arg2)
{
   int *pipefdPC = arg1;
   int *pipefdCP = arg2;

   // Configuration des pipes
   sclose(pipefdPC[1]);
   sclose(pipefdCP[0]);

   int fd_stdout = dup(1);  // sauvegarde du fd de stdout
   checkNeg(fd_stdout, "Dup failed\n");
   int ret = dup2(pipefdCP[1], 1);  // duplication de pipefdCP[1] sur fd 1
   checkNeg(ret, "Dup2 failed\n");  // ==> écrire sur fd 1 (écran) écrit en réalité sur pipefdCP[1]

   // Lecture sur pipe PC --> écriture sur 1 (=pipefdCP[1])
   InscriptionRequest ir;
   int nbTrans = sread(pipefdPC[0], &ir, sizeof(InscriptionRequest));
   while (nbTrans != 0) {
      int rep = (ir.nbYearPastInEducation < 3) ? 1 : 0;
      nwrite(1, &rep, sizeof(int));
      nbTrans = sread(pipefdPC[0], &ir, sizeof(InscriptionRequest));
   }

   // Fermeture des pipes
   sclose(pipefdPC[0]);
   sclose(pipefdCP[1]);
   ret = dup2(fd_stdout, 1);  // restauration de stdout sur le fd 1
   checkNeg(ret, "Dup2 failed\n");
   sclose(fd_stdout);
   printf("Moi, le fils, j'ai fini mon boulot !\n");
}


int main(int argc, char **argv)
{
   // Création des pipes
   // PC: parent -> child
   int pipefdPC[2];
   spipe(pipefdPC);

   // CP: child -> parent
   int pipefdCP[2];
   spipe(pipefdCP);

   // Création d'un processus fils
   pid_t childId = fork_and_run2(child, pipefdPC, pipefdCP);

   // Configuration des pipes
   sclose(pipefdPC[0]);
   sclose(pipefdCP[1]);

   // Lecture sur 0 -> écriture dans pipe PC
   InscriptionRequest ir;
   int rep;
   int nbInscriptions = 0;
   int i = 0;
   int nbTrans = sread(0, &ir, sizeof(InscriptionRequest));
   while (nbTrans != 0) {
      if (i % 2 == 0) {
         // Envoi au fils
         nwrite(pipefdPC[1], &ir, sizeof(InscriptionRequest));
         printf("Attente trt par le fils .... %s %s %i\n", ir.firstname, ir.name, ir.nbYearPastInEducation);
         sread(pipefdCP[0], &rep, sizeof(int));
         if (rep) {
            nbInscriptions++;
         }
      } else {
         printf("Trt par le père : %s %s %i\n", ir.firstname, ir.name, ir.nbYearPastInEducation);
         if (ir.nbYearPastInEducation < 3) {
            nbInscriptions++;
         }
      }
      i++;
      nbTrans = sread(0, &ir, sizeof(InscriptionRequest));
   }

   printf("\nOK, mon fils n'a plus rien à me transmettre\n");

   // Fermeture des pipes
   sclose(pipefdCP[0]);
   sclose(pipefdPC[1]);
   printf("Père : Total des inscriptions acceptées : %i\n", nbInscriptions);

   swaitpid(childId, NULL, 0);
}
