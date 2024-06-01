#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char **argv)
{
    char *str1 = "trois .. deux .. un ..";
    char *str2 = "partez !";

    if (write(1, str1, strlen(str1)) == -1) {
        perror("Write failed");
        exit(10);
    }

    /* Création du processus fils */
    int childId = fork();
    if (childId == -1) { 
        perror("Fork failed");
        exit(20);
    }

    if (!childId) {
        /* Dans le processus enfant */
        if ((write(1, str2, strlen(str2))) == -1) {
            perror("Write failed");
            exit(10);
        }
    }
}
