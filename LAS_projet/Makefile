CC=gcc
CCFLAGS=-D_DEFAULT_SOURCE -D_XOPEN_SOURCE -D_BSD_SOURCE -std=c11 -pedantic -Wvla -Wall -Werror
LDFLAGS=-pthread

all: server client 

server: server.o network.o ipc.o jeu.o utils_v1.o
	$(CC) $(CCFLAGS) $(LDFLAGS) -o server server.o network.o ipc.o jeu.o utils_v1.o

client: client.o network.o ipc.o jeu.o utils_v1.o 
	$(CC) $(CCFLAGS) $(LDFLAGS) -o client client.o network.o ipc.o jeu.o utils_v1.o

server.o: server.c network.h ipc.h jeu.h utils_v1.h messages.h classement.h
	$(CC) $(CCFLAGS) -c server.c 

client.o: client.c network.h ipc.h jeu.h utils_v1.h messages.h classement.h
	$(CC) $(CCFLAGS) -c client.c

network.o: network.c network.h
	$(CC) $(CCFLAGS) -c network.c

ipc.o: ipc.c ipc.h
	$(CC) $(CCFLAGS) -c ipc.c

jeu.o: jeu.c jeu.h
	$(CC) $(CCFLAGS) -c jeu.c

utils_v1.o: utils_v1.c utils_v1.h
	$(CC) $(CCFLAGS) -c utils_v1.c 

clean:
	rm -f *.o server client