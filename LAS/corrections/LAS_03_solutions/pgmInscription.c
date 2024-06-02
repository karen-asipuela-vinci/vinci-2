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

   int fd_stdout = dup(1); // sauvegarde du fd de stdout
   checkNeg(fd_stdout, "Dup failed\n");
   int ret = dup2(pipefdCP[1], 1); // duplication de pipefdCP[1] sur fd 1
   checkNeg(ret, "Dup2 failed\n"); // ==> écrire sur fd 1 (écran) écrit en réalité sur pipefdCP[1]

   // Lecture sur pipe PC --> écriture sur 1 (=pipefdCP[1])
   InscriptionRequest ir;
   int nbTrans = sread(pipefdPC[0], &ir, sizeof(InscriptionRequest));
   while (nbTrans != 0)
   {
      int rep = (ir.nbYearPastInEducation < 3) ? 1 : 0;
      nwrite(1, &rep, sizeof(int));
      nbTrans = sread(pipefdPC[0], &ir, sizeof(InscriptionRequest));
   }

   // Fermeture des pipes
   sclose(pipefdPC[0]);
   sclose(pipefdCP[1]);
   ret = dup2(fd_stdout, 1); // restauration de stdout sur le fd 1
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
   while (nbTrans != 0)
   {
      if (i % 2 == 0)
      {
         // Envoi au fils
         nwrite(pipefdPC[1], &ir, sizeof(InscriptionRequest));
         printf("Attente trt par le fils .... %s %s %i\n", ir.firstname, ir.name, ir.nbYearPastInEducation);
         sread(pipefdCP[0], &rep, sizeof(int));
         if (rep)
         {
            nbInscriptions++;
         }
      }
      else
      {
         printf("Trt par le père : %s %s %i\n", ir.firstname, ir.name, ir.nbYearPastInEducation);
         if (ir.nbYearPastInEducation < 3)
         {
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

/*
Écrivez un programme pgmInscription.c traitant des demandes d’inscription.
Le programme lira un fichier binaire nommé “DemandesInscriptions.bin”,
contenant des demandes d’inscriptions.
La lecture de ce fichier se fera en utilisant la redirection de l’entrée
standard présente dans le shell de la manière suivante :

./pgmInscription < DemandesInscriptions.bin

Le programme principal validera une demande d’inscription sur deux.
L'autre demande sera chaque fois envoyée à un processus fils pour être
validée par ce dernier.
Cette validation sera simplement constituée d’une vérification du nombre
d’années du passé de l’étudiant. L’étudiant est accepté si son nombre d’années
passées dans l’enseignement est < 3, et refusé sinon.
Le père enverra les demandes d’inscriptions via un pipe au processus fils.
Le fils répondra au père par 0 (inscription refusée) ou 1 (inscription acceptée)
via un deuxième pipe. Le processus père centralisera et affichera le nombre
total d’inscriptions acceptées par lui et son fils.

Voici une liste d’étapes à réaliser :

1. Récupérez et exécutez le programme « createInscriptionRequests.c ».
Celui-ci créera un fichier nommé « DemandesInscriptions.bin ».
Il s’agit d’un fichier binaire contenant des enregistrements de demandes
d’inscriptions.

2. Créez un programme « pgmInscription.c » pour effectuer le travail de
validation.

3. Mettez en place la communication entre le père et le fils :
création et configuration des pipes nécessaires.

4. Prenez connaissance de la structure des enregistrements à traiter
(fichier inscriptionRequest.h).
La lecture des enregistrements et leur transmission au fils doit se faire
proprement à l'aide d’appels système read et write.

5. Réalisez les affichages dans le père suivant le cas :
   1. « Trt par le père : <nom de l’étudiant> <nombre années du passé> »
   2. « Attente trt fils : <nom de l’étudiant> <nombre années du passé> »

6. Implémentez la validation de chaque inscription
(simple test sur nombre d’années du passé), ainsi que l’obtention au niveau
du père du total des inscriptions validées.

7. Programmez proprement, en vérifiant l'absence d'erreur lors de chaque
appel système, et en veillant à ne pas laisser de ressources pendantes inutiles.
*/

/*
3.D. Suite de l’exercice 3.C.

1. Si vous ne l’avez pas encore fait, utilisez une fonction de type
fork_and_run() du module utils pour la création et l’exécution du code du
processus fils. On ne veut pas que des informations soient placées dans des
variables globales, donc les file descriptors des pipes devront être passés
en paramètres de cette fonction fork_and_run(), puis de son handler.

2. À l’aide d’un appel système dup2, redirigez dans le fils le fd de la sortie
standard pour qu’il serve à l’écriture d’informations vers le père.

3. Lorsque le fils réalise qu’il a fini son travail, il libère proprement ses
ressources, puis affiche “Moi, le fils, j’ai fini mon boulot” à la console
avant de se terminer. Zut, la sortie standard n’est plus disponible à cause
du point 2 !
Modifiez votre code pour pouvoir à nouveau utiliser la sortie standard dans
le fils lorsqu'il ne doit plus communiquer au père.

4. Le père vérifie que le fils a bien fermé le pipe qu’il utilisait pour
communiquer vers le père, puis il affiche le message “OK, mon fils n’a plus
rien à me transmettre” à la sortie standard. Le père attend enfin d'être sûr
que le fils se termine avant de se terminer lui-même.
*/