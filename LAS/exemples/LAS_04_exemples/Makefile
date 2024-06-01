CFLAGS=-std=c11 -pedantic -Wall -Wvla -Werror -D_DEFAULT_SOURCE

ALL= exemple9 exemple10 exemple11

all: $(ALL)

exemple9: exemple9.o utils_v1.o
	gcc $(CFLAGS) -o exemple9 exemple9.o utils_v1.o

exemple9.o: exemple9.c utils_v1.h
	gcc $(CFLAGS) -c exemple9.c

exemple10: exemple10.o utils_v1.o
	gcc $(CFLAGS) -o exemple10 exemple10.o utils_v1.o

exemple10.o: exemple10.c utils_v1.h
	gcc $(CFLAGS) -c exemple10.c

exemple11: exemple11.o utils_v1.o
	gcc $(CFLAGS) -o exemple11 exemple11.o utils_v1.o

exemple11.o: exemple11.c utils_v1.h
	gcc $(CFLAGS) -c exemple11.c

utils_v1.o: utils_v1.c utils_v1.h
	gcc $(CFLAGS) -c utils_v1.c

clean:
	rm -f *.o
	rm -f $(ALL)