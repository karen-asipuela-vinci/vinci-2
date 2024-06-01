CFLAGS=-std=c11 -pedantic -Wall -Wvla -Werror -D_DEFAULT_SOURCE

PROGS=exemple2 exemple3 exemple4 exemple5

all: $(PROGS)

exemple2: exemple2.o utils_v1.o
	gcc $(CFLAGS) -o exemple2 exemple2.o utils_v1.o

exemple2.o: exemple2.c utils_v1.h
	gcc $(CFLAGS) -c exemple2.c

exemple3: exemple3.o utils_v1.o
	gcc $(CFLAGS) -o exemple3 exemple3.o utils_v1.o

exemple3.o: exemple3.c utils_v1.h
	gcc $(CFLAGS) -c exemple3.c

exemple4: exemple4.o utils_v1.o
	gcc $(CFLAGS) -o exemple4 exemple4.o utils_v1.o

exemple4.o: exemple4.c utils_v1.h
	gcc $(CFLAGS) -c exemple4.c

exemple5: exemple5.o utils_v1.o
	gcc $(CFLAGS) -o exemple5 exemple5.o utils_v1.o

exemple5.o: exemple5.c utils_v1.h
	gcc $(CFLAGS) -c exemple5.c

utils_v1.o: utils_v1.c utils_v1.h
	gcc $(CFLAGS) -c utils_v1.c

clean:
	rm -f *.o
	rm -f $(PROGS)
