CFLAGS =-std=c11 -pedantic -Wall -Wvla -Werror -D_DEFAULT_SOURCE
ALL = exemple6 exemple7 exemple8

all: $(ALL)

exemple6: utils_v1.o exemple6.o
	cc $(CFLAGS) -o exemple6 utils_v1.o exemple6.o

exemple7: utils_v1.o exemple7.o
	cc $(CFLAGS) -o exemple7 utils_v1.o exemple7.o

exemple8: utils_v1.o exemple8.o
	cc $(CFLAGS) -o exemple8 utils_v1.o exemple8.o

exemple6.o: utils_v1.h exemple6.c
	cc $(CFLAGS) -c exemple6.c 
	
exemple7.o: utils_v1.h exemple7.c
	cc $(CFLAGS) -c exemple7.c 

exemple8.o: utils_v1.h exemple8.c 
	cc $(CFLAGS) -c exemple8.c 

utils_v1.o: utils_v1.c utils_v1.h
	cc $(CFLAGS) -c utils_v1.c 

clean:
	rm -f *.o
	rm -f $(ALL)

# for dev purpose
clear:
	clear
	
dev: clear clean exemple6
	./exemple6