
#include "messages.h"
#include "player.h"

#define SHM_KEY  5
#define SEM_KEY  6
#define PERM 0666

// à supprimer ???
// void initializeSharedMemory();

int initializeSemaphores();

Ranking* initializeSharedMemory(){
    int shm_id = sshmget(SHM_KEY, sizeof(Ranking), IPC_CREAT | PERM);
    Ranking* ranking = (Ranking*)sshmat(shm_id);

    return ranking;
}

int initializeSemaphores(){
    return sem_create(SEM_KEY, 1, 0600, 0);
}

int getSemaphoreID(){
    return sem_get(SEM_KEY, 1, 0400);
}

//ajouter creation de pipes??
//RAPPEL deux pipes : un dans chaque sens
