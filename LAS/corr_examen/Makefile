CFLAGS = -std=c11 -pedantic -Wall -Wvla -Werror -Wno-unused-variable -D_DEFAULT_SOURCE

all: testmult server client

server: server.o utils_v1.o
	gcc $(CFLAGS) -o server server.o utils_v1.o

client: client.o utils_v1.o
	gcc $(CFLAGS) -o client client.o utils_v1.o

testmult: testmult.o utils_v1.o
	gcc $(CFLAGS) -o testmult testmult.o utils_v1.o

testmult.o: testmult.c utils_v1.h
	gcc $(CFLAGS) -c testmult.c

server.o: server.c utils_v1.h
	gcc $(CFLAGS) -c server.c	

client.o: client.c utils_v1.h
	gcc $(CFLAGS) -c client.c	

utils_v1.o: utils_v1.c utils_v1.h
	gcc $(CFLAGS) -c utils_v1.c

clean:
	rm -f *.o
	rm -f testmult
	rm -f server
	rm -f client