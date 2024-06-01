#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "../../utils_v1.h"

#define MAX 80

//*****************************************************************************
// USAGE
//*****************************************************************************
void checkUsage(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: %s file1 file2\n", argv[0]);
  }
}


//*****************************************************************************
// READ FUNCTIONS
//*****************************************************************************
int idx = -1;
int size = -1;
char buffer[MAX];

void readBlock() {
  if (size != 0 && idx == size) {
    size = read(0, buffer, MAX);
    checkNeg(size, "Error READ");
    idx = 0;
  }
}

bool eof() {
  readBlock();
  return size == 0;
}

char readChar() {
  char res = buffer[idx];
  idx++;
  return res;
}

void readPrefix(char* pref, int* lengthPref, int* lengthTot, int max) {
  *lengthPref = 0;
  *lengthTot = 0;
  
  bool eol = false;
  while(!eof() && !eol) {
    char current = readChar();
    eol = current == '\n';
    (*lengthTot)++;
    
    if (*lengthPref < max) {
      pref[*lengthPref] = current;
      (*lengthPref)++;
    }
  }
}

//*****************************************************************************
// MAIN
//*****************************************************************************

int main (int argc, char *argv[]) {
  checkUsage(argc, argv);
  int r;
  
  int fd1 = open(argv[1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
  checkNeg(fd1, "Error OPEN");
  int fd2 = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, 0644);
  checkNeg(fd2, "Error OPEN");
  
  while(!eof()) {
    int tot;
    int pref;
    char line[MAX];
    readPrefix(line, &pref, &tot, MAX);
    
    if (tot <= MAX && 'A' <= line[0] && line[0] <= 'Z') { // OU isupper()
      r = write(fd1, line, pref);
      checkCond(r != pref, "Error WRITE");
    } else if (tot <= MAX && 'a' <= line[0] && line[0] <= 'z') { // OU islower()
      r = write(fd2, line, pref);
      checkCond(r != pref, "Error WRITE");
    } 
  }
  
  r = close(fd1);
  checkNeg(r, "Error CLOSE");
  r = close(fd2);
  checkNeg(r, "Error CLOSE");
}