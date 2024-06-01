#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char **argv)
{    
    int a = 5;
    
    /* Création du processus fils */
    int childId = fork();
    if (childId == -1) {
        perror("Fork failed");
        exit(10);
    }
    
    printf("La variable childId vaut %d\n", childId);
    
    if (childId) { 
        /* Dans le processus parent */
        int b = 5*a;
        printf("Parent : a = %d et b = %d\n", a, b);
    } else { 
        /* Dans le processus enfant */
        int b = 2*a;
        printf("Enfant : a = %d et b = %d\n", a, b);
    }
}