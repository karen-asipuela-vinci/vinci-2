#ifndef _IPC_H_
#define _IPC_H_

#include "ranking.h"

#define SHM_KEY  5
#define SEM_KEY  6
#define PERM 0666

Ranking* initializeSharedMemory();

int initializeSemaphores();

int getSemaphoreID();

#endif // _IPC_H_