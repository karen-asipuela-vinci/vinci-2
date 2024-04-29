#include "ipc.h"
#include "player.h"
#include "utils_v1.h"
#include "messages.h"
#include <sys/sem.h>
#include <stdlib.h>

Ranking* initializeSharedMemory(){
    int shm_id = sshmget(SHM_KEY, sizeof(Ranking), IPC_CREAT | PERM);
    Ranking* ranking = (Ranking*)sshmat(shm_id);

    return ranking;
}

int initializeSemaphores(){
    return sem_create(SEM_KEY, 1, 0600, 0);
}

// erreur avec le nombre d'arguments.. corrigé
int getSemaphoreID(){
    int semflg = IPC_CREAT | 0400; // Droits de lecture
    int sem_id = semget(SEM_KEY, 1, semflg);
    if (sem_id == -1) {
    perror("Erreur lors de la création du sémaphore");
    exit(EXIT_FAILURE);
}
return sem_id;
}
