#ifndef _NETWORK_H_
#define _NETWORK_H_

#include <sys/socket.h>
#include "player.h"
#include "messages.h"
#include "utils_v1.h"
#define BACKLOG 5


/** 
 * PRE:  serverIP: a valid IP address
 *      serverPort: a valid port number
 * POST: on success, connects to serverIP:serverPort and returns the socket file descriptor ;
 * RES:  return socket file descriptor
 */

int initSocketClient(char *serverIP, int serverPort);
/** 
 * PRE:  sockfd: a valid socket file descriptor
 *       msg: a valid StructMessage
 * POST: sends msg to sockfd and receives response
*/

void sendMessageAndReceiveResponse(int sockfd, StructMessage *msg);
/** 
 * PRE:  tabPlayers: a valid array of Player
 *      nbPlayers: the number of players in tabPlayers
 * POST: disconnects all players in tabPlayers
*/

void disconnect_players(Player *tabPlayers, int nbPlayers);
/**
 * PRE:  serverPort: a valid port number
 * POST: on success, binds a socket to 0.0.0.0:serverPort and listens to it ;
 *       on failure, displays error cause and quits the program
 * RES:  return socket file descriptor
 */
int initSocketServer(int port);

#endif
