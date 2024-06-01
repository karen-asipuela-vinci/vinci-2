#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>

#include "../../utils_v1.h"

#define MAX 80

//*****************************************************************************
// USAGE
//*****************************************************************************
void checkUsage(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: %s file1 file2\n", argv[0]);
    exit(EXIT_FAILURE);
  }
}

//*****************************************************************************
// MAIN
//*****************************************************************************

int main(int argc, char **argv){

  checkUsage(argc, argv);

  char c;
  char bufRd[MAX+1];    /* +1 pour '\n' */
  int nbCharRd, nbCharWr;
  bool lnc = false; /* ligne non conforme (i.e. ne commence pas par une lettre) */

  int fd, fd1, fd2; /* file descriptors */  
  fd1 = open(argv[1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
  checkNeg(fd1, "Error OPEN");
  fd2 = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, 0644);
  checkNeg(fd2, "Error OPEN");
    
  while ((nbCharRd = read(0, bufRd, MAX+1))) { /* Boucle de lecture */
    checkNeg(nbCharRd,"Error reading file");

    if (bufRd[nbCharRd-1] == '\n'){ /* Ligne ne dépasse pas MAX caractères */
      bufRd[nbCharRd]='\0';  /* suppression du '\n' */
      if (isupper(bufRd[0]))
        fd = fd1; /* fd sur fichier "Maj" */
      else if (islower(bufRd[0]))
        fd = fd2; /* fd sur fichier "min" */
      else 
        lnc = true;
      if (!lnc){ /* Ligne conforme --> écriture dans fichier fd */
        nbCharWr = write(fd,bufRd,nbCharRd); 
        checkCond(nbCharWr != nbCharRd, "Error writing file");
      }
    } else {  /* Ligne trop longue --> vider le buffer de lecture clavier */
      while ((nbCharRd = read(0,&c,1)) && (c != '\n'))
        checkNeg(nbCharRd,"Error reading stdin");
    }
  }

  checkNeg(close(fd1), "Error CLOSE");
  checkNeg(close(fd2), "Error CLOSE");
}
