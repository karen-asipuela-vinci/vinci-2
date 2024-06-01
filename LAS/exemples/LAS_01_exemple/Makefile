CFLAGS=-std=c11 -pedantic -Wall -Wvla -Werror -D_DEFAULT_SOURCE

exemple01: exemple01.o utils_v1.o
	gcc $(CFLAGS) -o exemple01 exemple01.o utils_v1.o

exemple01.o: exemple01.c utils_v1.h
	gcc $(CFLAGS) -c exemple01.c

utils_v1.o: utils_v1.c utils_v1.h
	gcc $(CFLAGS) -c utils_v1.c

clean:
	rm -f *.o
	rm -f exemple01 test
