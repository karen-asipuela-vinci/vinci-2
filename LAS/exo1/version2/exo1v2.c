#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "utils_v1.h"

#define FILENAME "entiers10000000"
#define BUFFERSIZE 10000000

void writeFile (char* file);
void readFile (char* file);

int main(int argc, char **argv) {
  writeFile(FILENAME);
}

//fonction d'écriture
void writeFile(char* file) {

    /* Opening the file in write mode only, s'il y a du contenu, on l'efface, 
    et si n"exite pas, on le créé et dans ce cas-là, on défini les droits*/
    int fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);

    //on écrit les nombres dans le fichier
    //1 à 1
    for (int i = 0; i <= BUFFERSIZE; i++) {
        //on l'écrit 1 à 1 :
        write(fd, &i, sizeof(int));
    }
  
    //close
    int res = close(fd);
}