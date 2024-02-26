#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "utils_v1.h"

#define FILENAME "entiers10000000"
#define BUFFERSIZE 10 000 000

void writeFile (char* file);
void readFile (char* file);

int main(int argc, char **argv) {
  writeFile(FILENAME);
}

//fonction d'écriture
void writeFile(char* file) {
    //on l'ouvre en mode écriture
  FILE* fp = fopen(file, "wb");
  if (fp == NULL) {
    printf("Failed to open file for writing.\n");
    return;
  }

  for (int i = 0; i <= BUFFERSIZE; i++) {
    //on l'écrit 1 à 1 :
    fwrite(&i, sizeof(int), 1, fp);
  }

  fclose(fp);
}

