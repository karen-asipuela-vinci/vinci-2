#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../utils_v1.h"

#define BUFFER_SIZE 10

//*****************************************************************************
// CLEAR STDIN
//*****************************************************************************

// POST: Read all the characters on stdin up and including a '\n'
//       Moreover, the program is abruptly terminated when an error occurs.
void clearStdin() {
    char c;
    int nbCharRd = read(0, &c, 1);
    while(nbCharRd == 1 && c != '\n') {
        nbCharRd = read(0, &c, 1);
    }
    checkNeg(nbCharRd, "Error reading stdin");
}

//*****************************************************************************
// MAIN
//*****************************************************************************

int main (int argc, char **argv) {
    
    // An extra byte for '\0' at the end of the string is not required
    // because "string.h" is not used in this program.
    char bufRd[BUFFER_SIZE];
    
    printf("Introduisez votre ligne (max %d caractères): \n",BUFFER_SIZE);
    
    int nbCharRd = read(0, bufRd, BUFFER_SIZE);
    while(nbCharRd > 0) { 
        if(bufRd[nbCharRd - 1] == '\n') { 
            int res = write(1, bufRd, nbCharRd);
            checkCond(res != nbCharRd, "error wrinting stdout");
        } else { 
            printf("Erreur: la ligne introduite fait plus de %d caractères.\n",BUFFER_SIZE);
            clearStdin();
        }
        printf("Introduisez votre ligne (max %d caractères): \n",BUFFER_SIZE);
        nbCharRd = read(0, bufRd, BUFFER_SIZE);
    }

    checkNeg(nbCharRd, "Error reading stdin");
}


/*

STDIN_FILENO is a macro defined in <unistd.h>. 
At least for POSIX.1 compliant systems, it's required to be defined as 0. 
Similarly, STDOUT_FILENO is 1 and STDERR_FILENO is 2.

From /usr/include/unistd.h

// Standard file descriptors.
#define STDIN_FILENO    0       // Standard input. 
#define STDOUT_FILENO   1       // Standard output.  
#define STDERR_FILENO   2       // Standard error output.  

*/