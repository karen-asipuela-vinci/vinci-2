#ifndef _MESSAGES_H_
#define _MESSAGES_H_
#include "score.h"

#define SERVER_PORT 9502
#define SERVER_IP "127.0.0.1" /* localhost */
#define MAX_PSEUDO 256

#define INSCRIPTION_REQUEST 10
#define INSCRIPTION_OK 11
#define INSCRIPTION_KO 12
#define CURRENT_TUILE 13
#define FINISHED_PLAYING 14
#define FINISH_GAME 15
#define FINAL_SCORE 16
#define CANCEL_GAME 17
#define FINAL_RANKING 18


/* struct message used between server and client */
typedef struct
{
  char messageText[MAX_PSEUDO];
  int code;
  int tuile;
  Ranking* scores;
} StructMessage;
#endif
