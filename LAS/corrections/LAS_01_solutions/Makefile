CFLAGS=-std=c11 -pedantic -Wall -Wvla -Werror -D_DEFAULT_SOURCE

PROGS= ex01.1 ex01.2 ex01.3 ex01.4

ALL: $(PROGS)

ex01.1: ex01.1.o 
	gcc $(CFLAGS) -o ex01.1 ex01.1.o

ex01.1.o: ex01.1.c
	gcc $(CFLAGS) -c ex01.1.c
  
ex01.2: ex01.2.o utils_v1.o
	gcc $(CFLAGS) -o ex01.2 ex01.2.o utils_v1.o

ex01.2.o: ex01.2.c ../../utils_v1.h
	gcc $(CFLAGS) -c ex01.2.c

ex01.3: ex01.3.o utils_v1.o
	gcc $(CFLAGS) -o ex01.3 ex01.3.o utils_v1.o

ex01.3.o: ex01.3.c ../../utils_v1.h
	gcc $(CFLAGS) -c ex01.3.c

ex01.4: ex01.4.o utils_v1.o
	gcc $(CFLAGS) -o ex01.4 ex01.4.o utils_v1.o

ex01.4.o: ex01.4.c ../../utils_v1.h
	gcc $(CFLAGS) -c ex01.4.c
    
utils_v1.o: ../../utils_v1.h ../../utils_v1.c
	gcc $(CFLAGS) -c ../../utils_v1.c

clean:
	rm -f *.o
	rm -f $(PROGS)
