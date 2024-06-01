CFLAGS=-std=c11 -pedantic -Wall -Wvla -Werror -D_DEFAULT_SOURCE

PROGS=Ex2Aa Ex2Ab Ex2Ac Ex2Ad Ex2Ae Ex2Ba Ex2Bb Ex2Bd Ex2C

all: $(PROGS)

Ex2Aa: Ex2Aa.c 
	cc $(CFLAGS) -o Ex2Aa Ex2Aa.c

Ex2Ab: Ex2Ab.c 
	cc $(CFLAGS) -o Ex2Ab Ex2Ab.c

Ex2Ac: Ex2Ac.c 
	cc $(CFLAGS) -o Ex2Ac Ex2Ac.c

Ex2Ad: Ex2Ad.c 
	cc $(CFLAGS) -o Ex2Ad Ex2Ad.c

Ex2Ae: Ex2Ae.c 
	cc $(CFLAGS) -o Ex2Ae Ex2Ae.c

Ex2Ba: Ex2Ba.c 
	cc $(CFLAGS) -o Ex2Ba Ex2Ba.c

Ex2Bb: Ex2Bb.c 
	cc $(CFLAGS) -o Ex2Bb Ex2Bb.c

Ex2Bd: Ex2Bd.c utils_v1.o
	cc $(CFLAGS) -o Ex2Bd Ex2Bd.c utils_v1.o

Ex2C: Ex2C.c utils_v1.o
	cc $(CFLAGS) -o Ex2C Ex2C.c utils_v1.o

utils_v1.o: utils_v1.c utils_v1.h
	cc $(CFLAGS) -c utils_v1.c

clean:
	rm -f *.o
	rm -f $(PROGS)
