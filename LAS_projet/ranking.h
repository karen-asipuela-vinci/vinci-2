#ifndef _RANKING_H_
#define _RANKING_H_
#include "score.h"

#define MAX_PLAYERS 4

typedef struct Ranking{
    Score scores[MAX_PLAYERS];
    int nbPlayers;
} Ranking;

#endif