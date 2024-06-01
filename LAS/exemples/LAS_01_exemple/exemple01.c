#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "utils_v1.h"

#define BUFFERSIZE 80
#define FILENAME "test"

void writeFile (char* file);
void readFile (char* file);

int main(int argc, char **argv) {
  writeFile(FILENAME);
  readFile(FILENAME);
}


void writeFile (char* file) {
  /* buffer */
  char bufRd[BUFFERSIZE]; 
	
  /* Opening the file in write mode */
  int fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
  checkNeg(fd, "Error opening file");
 
  /* Reading STDIN, then writing file, up to EOF (Ctrl-D) */
  char* msg = "Enter text lines (Ctrl-D to terminate):\n";
  int len = strlen(msg);
  int nbCharWr = write(1, msg, len);
  checkCond(nbCharWr != len,"Error writing on stdout");
  
  int nbCharRd = read(0, bufRd, BUFFERSIZE);
  while (nbCharRd > 0) {
    // For the first use of the "write" function, 
    // we assume that it is able to write "BUFFERSIZE" bytes at once. 
    // Be careful, this assumption is too strong. 
    // We are going to fix this later in the course.
    nbCharWr = write(fd, bufRd, nbCharRd);
    checkCond(nbCharWr != nbCharRd,"Error writing file");
    nbCharRd = read(0, bufRd, BUFFERSIZE);
  }

  checkNeg(nbCharRd,"Error reading stdin");

  /* Closing fd */
  int res = close(fd);
  checkNeg(res,"Error closing fd");
}

void readFile (char* file) {
  /* buffer */
  char bufRd[BUFFERSIZE]; 

  /* Opening the file in read mode */
  int fd = open(file, O_RDONLY);
  checkNeg(fd, "Error opening file");
 
  /* Reading file, then writing STDOUT, up to EOF */
  int nbCharRd = read(fd, bufRd, BUFFERSIZE);
  while (nbCharRd > 0) {
    int nbCharWr = write(1, bufRd, nbCharRd);
    checkCond(nbCharWr != nbCharRd,"Error writing stdout");
    nbCharRd = read(fd, bufRd, BUFFERSIZE);
  }

  checkNeg(nbCharRd,"Error reading file");

  /* Closing fd */
  int res = close(fd);
  checkNeg(res, "Error closing fd");    
}
