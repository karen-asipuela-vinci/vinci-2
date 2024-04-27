#include "ipc.h"
#include "player.h"
#include "utils_v1.h"
#include "messages.h"

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
    return sem_get(SEM_KEY, 1);
}
