#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>

#include "utils_v1.h"

#define BUFFERSIZE 50
#define TIMEMILLISEC 10000
#define NB_CHILD 2

volatile sig_atomic_t end = 0;

static void child_trt(void *pipeV)
{
	int *pipe = (int *)pipeV;
	int i;
	char buffer[BUFFERSIZE];

	srand(getpid());
	sclose(pipe[0]);

	for (i = 0; i < 10; i++)
	{
		// alea
		int alea = rand() % TIMEMILLISEC;
		// stop process nb sec
		usleep(alea);

		sprintf(buffer, "Fils %i : inscription %i\n", getpid(), alea);
		swrite(pipe[1], buffer, strlen(buffer));
	}
	sclose(pipe[1]);
}

void exitHandler(int sig)
{
	end = 1;
}

int main(int argc, char **argv)
{
	int pipeInscr1[2], pipeInscr2[2];
	char buffer[BUFFERSIZE];
	int nbChar;
	struct pollfd fds[NB_CHILD];

	// pipe init
	spipe(pipeInscr1);
	fork_and_run1(child_trt, pipeInscr1);

	spipe(pipeInscr2);
	fork_and_run1(child_trt, pipeInscr2);

	ssigaction(SIGINT, exitHandler);
	ssigaction(SIGTERM, exitHandler);

	sclose(pipeInscr1[1]);
	sclose(pipeInscr2[1]);

	// init poll
	fds[0].fd = pipeInscr1[0];
	fds[0].events = POLLIN;

	fds[1].fd = pipeInscr2[0];
	fds[1].events = POLLIN;

	while (end == 0) 
	{
		spoll(fds, 2, 0); // pas de souci si le pipe est fermé côté écrivain --> pas d'événement POLLIN

		if (fds[0].revents & POLLIN)
		{
			nbChar = sread(pipeInscr1[0], buffer, BUFFERSIZE);

			nwrite(1, buffer, nbChar);
		}

		if (fds[1].revents & POLLIN)
		{
			nbChar = sread(pipeInscr2[0], buffer, BUFFERSIZE);

			nwrite(1, buffer, nbChar);
		}
	}

	sclose(pipeInscr1[0]);
	sclose(pipeInscr2[0]);
}
