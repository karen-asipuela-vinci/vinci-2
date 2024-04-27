
#ifndef _PAYER_H_
#define _PLAYER_H_

#include "messages.h"

#define MAX_PSEUDO 256


typedef struct Ranking{
    Score scores[MAX_PLAYERS];
    int nbPlayers;
} Ranking;



typedef struct Score
{
	char pseudo[MAX_PSEUDO];
    int score;
} Score;

#endif