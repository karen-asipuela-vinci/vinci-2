#ifndef _IPC_H_
#define _IPC_H_

#include "messages.h"
#include "player.h"
#include "utils_v1.h"

#define SHM_KEY  5
#define SEM_KEY  6
#define PERM 0666

void initializeSharedMemory();
int initializeSemaphores();
Ranking* initializeSharedMemory();
int initializeSemaphores();
int getSemaphoreID();

#endif // _IPC_H_