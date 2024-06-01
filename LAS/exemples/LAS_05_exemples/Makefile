CFLAGS=-std=c11 -pedantic -Wall -Wvla -Werror -D_DEFAULT_SOURCE 

ALL= exemple12 exemple13 exemple14

all: $(ALL)

exemple12: exemple12.c utils_v1.o
	gcc $(CFLAGS) -o exemple12 exemple12.c utils_v1.o

exemple13: exemple13.c utils_v1.o
	gcc $(CFLAGS) -o exemple13 exemple13.c utils_v1.o

exemple14: exemple14.c utils_v1.o
	gcc $(CFLAGS) -o exemple14 exemple14.c utils_v1.o


utils_v1.o: utils_v1.c utils_v1.h
	gcc $(CFLAGS) -c utils_v1.c

clean:
	rm -f *.o
	rm -f $(ALL)
