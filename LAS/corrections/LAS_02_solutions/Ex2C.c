#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#include "utils_v1.h"

#define NAMEWIDTH 21
#define BUFSIZE 256

/* Handlers pour les fork */
static void exec_ls(void *arg){
  char *scriptName = arg;
  printf("\nls -l %s:\n", scriptName);
  sexecl("/bin/ls", "ls", "-l", scriptName, NULL);
}

static void exec_cat(void *arg){
  char *scriptName = arg;  
  printf("\ncat %s:\n", scriptName);
  sexecl("/bin/cat", "cat", scriptName, NULL);
}

/* Main */  
int main(int argc, char **argv){
  /* Lecture du nom du script au clavier */ 
  printf("Entrez le nom du script (max %d caractères)\n", NAMEWIDTH - 1);
    
  char scriptName[NAMEWIDTH];
  int nbCharRd = sread(0, scriptName, NAMEWIDTH);
  /* Remplacement du \n pour utilisation du format %s */
  scriptName[nbCharRd - 1] = 0; 
    
  /* Création du fichier script avec permissions 700 */
  int fd = sopen(scriptName, O_WRONLY | O_TRUNC | O_CREAT, 0700);

  /* Faire un ls -l sur le nom du script créé */
  int c1 = fork_and_run1(exec_ls, scriptName);
  swaitpid(c1, NULL, 0);

  /* Ecriture du shebang dans le script */
  char* shebang = "#!/bin/bash\n";
  int szShebang = strlen(shebang);
  nwrite(fd, shebang, szShebang);

  /* Saisie du contenu du script */
  printf("\nSaisie du contenu de votre script (ctrl-d pour terminer).\n");
  char readBuffer[BUFSIZE];    
  int nbrRead;
  while ((nbrRead = sread(0, readBuffer, BUFSIZE)) != 0) {
    nwrite(fd, readBuffer, nbrRead);
  }

  /* Libérer les ressources ! */
  sclose(fd);
    
  int c2 = fork_and_run1(exec_cat, scriptName);
  swaitpid(c2, NULL, 0);

  /* Exécution du script enregistré */
  printf("\n./%s:\n", scriptName);
  sexecl(scriptName, scriptName, NULL);
}
