#ifndef _SCORE_H_
#define _SCORE_H_

#include "ranking.h"

#define MAX_PSEUDO 256
#define MAX_PLAYERS 4

typedef struct Score
{
    char pseudo[MAX_PSEUDO];
    int score;
} Score;

#endif