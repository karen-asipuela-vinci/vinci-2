#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "utils_v2.h"

#define BUFFER_SIZE 80

int main(int argc, char **argv)
{

    // création des pipes
    int pipePere[2];
    int pipeFils[2];

    spipe(pipePere);
    spipe(pipeFils);

    // enfant doit recevoir les pipes
    fork_and_run2(childMethod, pipePere, pipeFils);

    // parent ecrit[1]
    sclose(pipePere[0]);
    sclose(pipeFils[1]);

    // doit lire le texte
    char line[BUFFER_SIZE];
}

void childMethod(void *pipePere, void *pipeFils)
{
}