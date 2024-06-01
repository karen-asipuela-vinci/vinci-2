CFLAGS=-std=c11 -pedantic -Wall -Wvla -Werror -Wno-unused-variable -D_DEFAULT_SOURCE

ALL= 4.1a 4.1b 4.1c timer 4.3 random bonus

all: $(ALL)

4.1a: 4.1a.c utils_v1.o
	gcc $(CFLAGS) -o 4.1a 4.1a.c utils_v1.o

4.1b: 4.1b.c utils_v1.o
	gcc $(CFLAGS) -o 4.1b 4.1b.c utils_v1.o

4.1c: 4.1c.c utils_v1.o
	gcc $(CFLAGS) -o 4.1c 4.1c.c utils_v1.o

timer: 4.2.c utils_v1.o
	gcc $(CFLAGS) -o timer 4.2.c utils_v1.o

4.3: 4.3.c utils_v1.o
	gcc $(CFLAGS) -o 4.3 4.3.c utils_v1.o

random: 4.4.c utils_v1.o
	gcc $(CFLAGS) -o random 4.4.c utils_v1.o

bonus: 4.5.c utils_v1.o
	gcc $(CFLAGS) -o bonus 4.5.c utils_v1.o

utils_v1.o: utils_v1.c utils_v1.h
	gcc $(CFLAGS) -c utils_v1.c

clean:
	rm -f *.o
	rm -f $(ALL)
