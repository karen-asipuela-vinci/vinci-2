#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char **argv)
{
    // Sans \n:
    char *str1 = "trois .. deux .. un ..";
    char *str2 = "partez !";
    
    // Avec \n:
    //char *str1 = "trois .. deux .. un ..\n";
    //char *str2 = "partez !\n";
    
    
    printf("%s", str1);
    
    /* Création du processus fils */
    int childId = fork();
    if (childId == -1) { 
        perror("Fork failed");
        exit(20);
    }
    
    if (!childId){ 
        /* Dans le processus enfant */
        printf("%s", str2);
    }
}
