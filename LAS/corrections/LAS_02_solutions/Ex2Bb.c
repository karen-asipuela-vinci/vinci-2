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
    if (childId == -1)
    {
        perror("Fork failed");
        exit(20);
    }

    if (childId)
    {
        /* Dans le processus parent */
        int status;
        // attente de la fin du fils
        if (waitpid(childId, &status, 0) == -1)
        {
            perror("Wait failed");
            exit(30);
        }
        if ((write(1, str1, strlen(str1))) == -1)
        {
            perror("Write failed");
            exit(10);
        }
    }
    else
    {
        /* Dans le processus enfant */
        if ((write(1, str2, strlen(str2))) == -1)
        {
            perror("Write failed");
            exit(10);
        }
    }
}

/*
Modifiez votre programme afin que l’enfant affiche toujours "4 5 6\n"
avant que le parent n’affiche "1 2 3\n".
*/

/*
Modifiez votre programme afin que l’enfant se termine par un exit,
puis affiche l’exit code de ce processus enfant.
Consultez le man de waitpid pour trouver comment récupérer l’exit code du processus
enfant.
*/