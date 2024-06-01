CFLAGS = -std=c11 -pedantic -Wall -Wvla -Werror -Wno-unused-variable -D_DEFAULT_SOURCE

ALL= heartbeat pingpong robot

all: $(ALL)

heartbeat: ex5.1.c utils_v1.o
	gcc $(CFLAGS) -o heartbeat ex5.1.c utils_v1.o

pingpong: ex5.2.c utils_v1.o
	gcc $(CFLAGS) -o pingpong ex5.2.c utils_v1.o

robot: robot.c utils_v1.o
	gcc $(CFLAGS) -o robot robot.c utils_v1.o

utils_v1.o: utils_v1.c utils_v1.h
	gcc $(CFLAGS) -c utils_v1.c

clean:
	rm -f *.o
	rm -f $(ALL)