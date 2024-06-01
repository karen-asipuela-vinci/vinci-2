CFLAGS=-std=c11 -pedantic -Wall -Wvla -Werror -Wno-unused-variable -D_DEFAULT_SOURCE

ALL= 3a pipe pgmInscription createInscriptionRequests

all: $(ALL) 

3a: 3a.o utils_v1.o
	gcc $(CFLAGS) -o 3a 3a.o utils_v1.o

3a.o: 3a.c utils_v1.h 
	gcc $(CFLAGS) -c 3a.c

pipe: pipe.o utils_v1.o
	gcc $(CFLAGS) -o pipe pipe.o utils_v1.o

pipe.o: pipe.c utils_v1.h
	gcc $(CFLAGS) -c pipe.c
	
pgmInscription: utils_v1.o pgmInscription.o
	gcc $(CFLAGS) -o pgmInscription utils_v1.o pgmInscription.o

pgmInscription.o: pgmInscription.c inscriptionRequest.h
	gcc $(CFLAGS) -c pgmInscription.c

createInscriptionRequest: createInscriptionRequests.c inscriptionRequest.h
	gcc $(CFLAGS) -o createInscriptionRequests createInscriptionRequests.c

utils_v1.o: utils_v1.c utils_v1.h
	gcc $(CFLAGS) -c utils_v1.c 

# for dev purpose
clear:
	clear

clean:
	rm -f *.o
	rm -f DemandesInscriptions.bin
	rm -f $(ALL)

dev: clear all
	valgrind ./pipe ls grep "\.c$$"