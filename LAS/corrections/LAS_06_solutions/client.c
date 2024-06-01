#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "ipc_conf.h"
#include "utils_v2.h"

#define STRING_SIZE 10

//******************************************************************************
// STATIC FUNCTIONS
//******************************************************************************

static bool str_is_lower(char* s, int sz) {
  bool res = true;
  int i = 0;
  while(i != sz && res) {
    res =  'a' <= s[i] && s[i] <= 'z';
    i++;
  }
  return res;
}

static void usage(char *name) {
  printf("Usage: %s <10 lower case characters>\n", name);
}

//******************************************************************************
// MAIN FUNCTION
//******************************************************************************

int main (int argc, char *argv[]) {
  if (argc != 2 || strlen(argv[1]) != STRING_SIZE || !str_is_lower(argv[1], STRING_SIZE)) {
    usage(argv[0]);
    exit(EXIT_FAILURE);
  } 

  // Obtention de la mémoire partagée
  int shid = sshmget(CLIENT_SERVEUR_SHM_KEY, STRING_SIZE * sizeof(char), 0);
  char* s = sshmat(shid);

  // Initialisation de la mémoire partagée
  strncpy(s, argv[1], STRING_SIZE);
  
  // Obtention des sémaphores
  int sid = sem_get(CLIENT_SERVEUR_SEM_KEY, 2);
  
  // Synchronisation avec le serveur: 
  // up sur sem 0 --> autoriser l'accès à la shm par le serveur
  sem_up(sid, 0);
  
  // Synchronisation avec le serveur: 
  // down sur sem 1 --> demander l'accès à la shm (après traitement par le serveur)
  sem_down(sid, 1);
  
  // Lecture de la shm
  nwrite(1,s,STRING_SIZE);
  nwrite(1,"\n",1);
  
  sshmdt(s);
  
  exit(EXIT_SUCCESS);
}
