#ifndef _PLAYER_H_
#define _PLAYER_H_

#define MAX_PSEUDO 256

typedef struct Player
{
	char pseudo[MAX_PSEUDO];
	int sockfd;
	int pipefd[2];
} Player;

#endif