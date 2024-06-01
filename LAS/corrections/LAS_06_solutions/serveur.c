#include <stdlib.h>

#include "ipc_conf.h"
#include "utils_v2.h"

#define STRING_SIZE 10

//******************************************************************************
// MAIN FUNCTION
//******************************************************************************
int main (int argc, char *argv[]) {
  // Obtention de la mémoire partagée
  int shid = sshmget(CLIENT_SERVEUR_SHM_KEY, STRING_SIZE * sizeof(char), 0);
  char* s = sshmat(shid);
  
  // Obtention des sémaphores
  int sid = sem_get(CLIENT_SERVEUR_SEM_KEY, 2);
 
  // Synchronisation avec le client: 
  // down sur sem 0 --> demander l'accès à la shm (après initialisation par le client)
  sem_down(sid, 0);
  
  // Traitement de la shm
  int i = 0;
  while(i != STRING_SIZE) {
    s[i] &= 0x5F;  // mettre le 6e bit à 0 pour convertir une lettre ASCII minuscule en majuscule
    i++;
  }
  
  // Synchronisation avec le client:  
  // up sur sem 1 --> autoriser l'accès à la shm par le client
  sem_up(sid, 1);
 
  sshmdt(s);
  
  exit(EXIT_SUCCESS);
}