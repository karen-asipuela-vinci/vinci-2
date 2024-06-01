#include <unistd.h>

#include "utils_v1.h"

//***************************************************************************
// CHILD CODE
//***************************************************************************

void childhandler() {
  while(1) {
    sleep(2);
  }
}

//***************************************************************************
// MAIN
//***************************************************************************

int main() {
  pid_t childID = fork_and_run0(childhandler);
}


/*

$ ps -l -u $USER
F S   UID   PID  PPID  C PRI  NI ADDR SZ WCHAN  TTY          TIME CMD
0 S  1000   373   187  0  80   0 -  2603 -      tty1     00:00:00 4.1a

Le processus 4.1a est le fils. Il est en état S (interruptible sleep) et est orphelin 
car le processus père s'est terminé. Le processus orphelin est donc rattaché à 
un processus parent: systemd (PPID=187 ; ps -l 187).

$ kill -SIGUSR1 373

Le signal SIGUSR1 tue le processus fils (PID=373) qui n'apparaît plus dans le ps.

*/