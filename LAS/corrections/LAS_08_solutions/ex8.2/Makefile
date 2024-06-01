CC=gcc
CCFLAGS=-D_DEFAULT_SOURCE -D_XOPEN_SOURCE -D_BSD_SOURCE -std=c11 -pedantic -Wvla -Wall -Werror

ALL: ex8.2_MultiFils ex8.2_2Fils 

all: $(ALL)

ex8.2_2Fils : ex8.2_2Fils.o utils_v1.o
	$(CC) $(CCFLAGS) -o ex8.2_2Fils ex8.2_2Fils.o utils_v1.o

ex8.2_MultiFils : ex8.2_MultiFils.o utils_v1.o
	$(CC) $(CCFLAGS) -o ex8.2_MultiFils ex8.2_MultiFils.o utils_v1.o

ex8.2_2Fils.o: ex8.2_2Fils.c utils_v1.h 
	$(CC) $(CCFLAGS) -c ex8.2_2Fils.c 

ex8.2_MultiFils.o: ex8.2_MultiFils.c utils_v1.h 
	$(CC) $(CCFLAGS) -c ex8.2_MultiFils.c

utils_v1.o: utils_v1.c utils_v1.h
	$(CC) $(CCFLAGS) -c utils_v1.c 

clear :
		clear

clean :
	rm -f *.o
	rm -f $(ALL)
