#include <unistd.h>
#include "utils_v1.h"

void run_child1(void *pipefdPtr, void *cmdPtr);
void run_child2(void *pipefdPtr, void *cmdPtr);

int main(int argc, char **argv) {
   int pipefd[2];
   spipe(pipefd);
   
   fork_and_run2(run_child1, pipefd, argv[1]);
   fork_and_run2(run_child2, pipefd, &argv[2]);

   sclose(pipefd[0]);
   sclose(pipefd[1]);
   
   swait(NULL);
   swait(NULL);
}

void run_child1(void *pipefdPtr, void *cmdPtr) {
   int *pipefd = pipefdPtr;
   char *cmd = cmdPtr;

   sclose(pipefd[0]);
   int res = dup2(pipefd[1], 1);
   checkNeg(res, "Child1 dup2 failed\n");
   
   execlp(cmd, cmd, NULL);
   perror("Exec 2 failed");
}

void run_child2(void *pipefdPtr, void *cmdPtr) {
   int *pipefd = pipefdPtr;
   char **cmd = cmdPtr;

   sclose(pipefd[1]);
   int res = dup2(pipefd[0], 0);
   checkNeg(res, "Child2 dup2 failed\n");
   
   execvp(cmd[0], cmd);
   perror("Exec 2 failed");
}

/*

man exec : extraits

   int execlp(const char *file, const char *arg, ..., (char*) NULL);
   int execvp(const char *file, char *const argv[]);


   l - execl(), execlp(), execle()
       The  const  char *arg  and subsequent ellipses can be thought of as arg0, arg1, ..., argn.  Together they
       describe a list of one or more pointers to null-terminated  strings  that  represent  the  argument  list
       available to the executed program.  The first argument, by convention, should point to the filename asso‐
       ciated with the file being executed.

   v - execv(), execvp(), execvpe()
       The char *const argv[] argument is an array of pointers to null-terminated strings that represent the ar‐
       gument  list  available to the new program.  The first argument, by convention, should point to the file‐
       name associated with the file being executed.  The array  of  pointers  must  be  terminated  by  a  null
       pointer.

   p - execlp(), execvp(), execvpe()
       These  functions  duplicate the actions of the shell in searching for an executable file if the specified
       filename does not contain a slash (/) character.  The file is sought in the colon-separated list  of  di‐
       rectory  pathnames  specified in the PATH environment variable.

 */
