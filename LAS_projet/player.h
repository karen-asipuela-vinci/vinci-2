#ifndef _PAYER_H_
#define _PLAYER_H_

#define MAX_PSEUDO 256

typedef struct Player
{
    char pseudo[MAX_PSEUDO];
    int score;
    int sockfd;
    int pipefd_write[2];
    int pipefd_read[2];

} Player;

#endif
