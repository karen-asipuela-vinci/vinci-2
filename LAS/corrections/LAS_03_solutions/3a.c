#include <unistd.h>
#include <ctype.h>
#include "utils_v1.h"

#define BUFFERSIZE 80

void upper (char *str)
{
   int i = 0;
   while (str[i] != '\0') {
      str[i] = toupper(str[i]);
      i++;
   }
}

void run_child(void *argv)
{
   // PROCESSUS FILS
   int *pipefd = argv;
   char line[BUFFERSIZE + 1];

   // Cloture du descripteur d'écriture
   sclose(pipefd[1]);

   // Boucle de lecture sur le pipe, transformation en uppercase
   // et écriture à l'écran
   int nbChar;
   while ((nbChar = sread(pipefd[0], line, BUFFERSIZE)) != 0) {
      upper(line);
      nwrite(1, line, nbChar);
   }

   // Cloture du descripteur de lecture
   sclose(pipefd[0]);
}

int main(int argc, char **argv)
{
   char line[BUFFERSIZE + 1];

   // Création du pipe
   int pipefd[2];
   spipe(pipefd);

   // Création de l'enfant
   fork_and_run1(run_child, pipefd);

   // PROCESSUS PARENT
   // Cloture du descripteur pour la lecture
   sclose(pipefd[0]);

   // Boucle de lecture au clavier et écriture dans le pipe 
   int nbChar;
   while ((nbChar = sread(0, line, BUFFERSIZE)) != 0) {
      nwrite(pipefd[1], line, nbChar);
   }

   // Cloture du descripteur pour l'écriture
   sclose(pipefd[1]);
}
