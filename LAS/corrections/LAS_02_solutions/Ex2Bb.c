#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char **argv)
{
    char *str1 = "1 2 3\n";
    char *str2 = "4 5 6\n";

    /* Création du processus fils */
    int childId = fork();
    if (childId == -1) { 
        perror("Fork failed");
        exit(20);
    }

    if (childId) { 
        /* Dans le processus parent */
        int status;
        // attente de la fin du fils
        if (waitpid(childId, &status, 0) == -1) {
            perror("Wait failed");
            exit(30);
        }
        if ((write(1, str1, strlen(str1))) == -1) {
            perror("Write failed");
            exit(10);
        }
    } else { 
        /* Dans le processus enfant */
        if ((write(1, str2, strlen(str2))) == -1) {
            perror("Write failed");
            exit(10);
        }
    }
}