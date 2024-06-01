#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>
#include <sys/types.h>

#include "utils_v1.h"

#define MAX_XY  5

//***************************************************************************
// USER INTERFACE
//***************************************************************************

/**
 * Displays the game board
 * PRE: board of dimensions nl x nc
 *      i,j: indices of a board element where i<nl && j<nc
 * POST: the board has been displayed (upper left corner
 *       on position (4,0)), indicating 'R' on (i,j)
 */
void printBoard (int nl, int nc, int i, int j) {
    colorOn(1,PURPLE_TEXT);
    printf("\n    ");
    for (int c=0; c<nc; c++)
        printf("%3i", c);
    printf("\n     ");
    for (int c=0; c<nc; c++)
        printf("---");
    printf("\n");
    for (int l=nl-1; l>=0; l--) {
        printf("%3i |", l);
        colorOn(1,CYAN_TEXT);
        for (int c=0; c<nc; c++) {
            if (l==i && c==j) {
                colorOn(1,YELLOW_TEXT);
                printf(" %c ", 'R');
                colorOn(1,CYAN_TEXT);
            }
            else {
                printf("   ");
            }
        }
        colorOn(1,PURPLE_TEXT);
        printf("| %i\n", l);
    }
    printf("     ");
    for (int c=0; c<nc; c++)
        printf("---");
    printf("\n    ");
    for (int c=0; c<nc; c++)
        printf("%3i", c);
    printf("\n\n");
    colorOff();
}

//***************************************************************************
// CHILD CODE
//***************************************************************************

volatile sig_atomic_t signum;

void handler (int num) {
   signum = num;
}

void run() {
   // CHILD
   int x = 0;
   int y = 0;
   printf("==> X = %d, Y = %d\n", x, y);
   printBoard(MAX_XY,MAX_XY,y,x);

   // Arming of signals SIGUSR1 and SIGUSR2
   ssigaction(SIGUSR1, handler);
   ssigaction(SIGUSR2, handler);

   // Definition of signal mask (all signals except SIGUSR1 & SIGUSR2)
   sigset_t set;
   ssigfillset(&set);
   ssigdelset(&set, SIGUSR1);
   ssigdelset(&set, SIGUSR2);
	    
   while (true) { 
      // Wait for a signal SIGUSR1 or SIGUSR2
      sigsuspend(&set);

      if (signum == SIGUSR1) {  // go up
         y++;
         y += MAX_XY;
         y %= MAX_XY;
      } else {  // SIGUSR2: go right
         x++;
         x += MAX_XY;
         x %= MAX_XY;
      }
      printf("==> X = %d, Y = %d\n", x, y);
      printBoard(MAX_XY,MAX_XY,y,x);
   }
}


//***************************************************************************
// PARENT CODE
//***************************************************************************

char readchar() {
   // read a line composed of 2 characters
   char c[2];
   sread(0,c,sizeof(c));
   
   // return the 1st read character
   return c[0];
}

int main () {
   // Block all signals
   sigset_t set1;
   ssigfillset(&set1);
   ssigprocmask(SIG_BLOCK, &set1, NULL);

   pid_t chid = fork_and_run0(run);

   // PARENT
   char* commands = "\nRobot commands:\n  'U' to go up\n" \
                     "  'R' to go right\n  'Q' to quit\n\n";
   nwrite(1,commands,strlen(commands));
   
   // Read a command
   char current = toupper(readchar());
   while (current != 'Q') {
      if (current == 'U')
         // Send SIGUSR1 to child
         skill(chid, SIGUSR1);
      else if (current == 'R')
         // Send SIGUSR2 to child
         skill(chid, SIGUSR2);
      else
         printf("Error: unknown command\n");
      
      // Read a command
      current = toupper(readchar());
   }
	
   // Kill child process
   skill(chid, SIGKILL);
}

