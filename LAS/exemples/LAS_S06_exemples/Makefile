CFLAGS=-std=c11 -pedantic -Wall -Wvla -Werror -Wno-unused-variable -D_DEFAULT_SOURCE

all: exemple15 exemple16

exemple15: utils_v2.o exemple15.o
	cc $(CFLAGS) -o exemple15 exemple15.o utils_v2.o  

exemple16: utils_v2.o exemple16.o
	cc $(CFLAGS) -o exemple16 exemple16.o utils_v2.o  

exemple15.o: utils_v2.h exemple15.c
	cc $(CFLAGS) -c exemple15.c  

exemple16.o: utils_v2.h exemple16.c
	cc $(CFLAGS) -c exemple16.c  

utils_v2.o: utils_v2.h utils_v2.c 
	cc $(CFLAGS) -c utils_v2.c 

# for dev purpose
clear:
	clear
	
clean:
	rm -f *.o
	rm -f exemple16
	rm -f exemple15
	ipcrm -a

dev1: all
	./exemple15
	ipcs
	
dev2: all
	./exemple16
	ipcs
