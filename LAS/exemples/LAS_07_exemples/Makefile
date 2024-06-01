CC=gcc

CCFLAGS=-D_DEFAULT_SOURCE -D_XOPEN_SOURCE -D_BSD_SOURCE -std=c11 -pedantic -Wvla -Wall -Werror

ALL= exemple17_Serveur exemple17_Client

all: $(ALL)

exemple17_Serveur: exemple17_Serveur.o utils_v1.o
						$(CC) $(CCFLAGS) -o exemple17_Serveur exemple17_Serveur.o utils_v1.o
						
exempleServeurSocket.o: exemple17_Serveur.c 
						$(CC) $(CCFLAGS) -c exemple17_Serveur.c

exemple17_Client: exempleClientSocket.o utils_v1.o
						$(CC) $(CCFLAGS) -o exemple17_Client exemple17_Client.o utils_v1.o

exempleClientSocket.o: exemple17_Client.c
						$(CC) $(CCFLAGS) -c exemple17_Client.c

utils_v1.o: utils_v1.c utils_v1.h
	$(CC) $(CCFLAGS) -c utils_v1.c

clean: 
	rm -f $(ALL) *.o