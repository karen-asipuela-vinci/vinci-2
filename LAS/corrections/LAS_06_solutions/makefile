CC=gcc
CFLAGS=-std=c11 -Werror=vla -pedantic -Wall -Wno-unused-variable -D_DEFAULT_SOURCE  

PRG = radar dashboard famille1 famille2 admin1 distributeur admin2 ecran client serveur admin3 switch train

all: $(PRG)
	
radar: ipc_conf.h utils_v2.h utils_v2.o radar.o
dashboard: ipc_conf.h utils_v2.h utils_v2.o dashboard.o

famille1: utils_v2.h utils_v2.o famille1.o
famille2: ipc_conf.h utils_v2.h utils_v2.o famille2.o

admin1: ipc_conf.h utils_v2.h utils_v2.o admin1.o 
distributeur: ipc_conf.h utils_v2.h utils_v2.o distributeur.o 
ecran: ipc_conf.h utils_v2.h utils_v2.o ecran.o 

admin2: ipc_conf.h utils_v2.h utils_v2.o admin2.o 
client: ipc_conf.h utils_v2.h utils_v2.o client.o
serveur: ipc_conf.h utils_v2.h utils_v2.o serveur.o

admin3: ipc_conf.h utils_v2.h utils_v2.o admin3.o 
switch: ipc_conf.h utils_v2.h utils_v2.o switch.o
train: ipc_conf.h utils_v2.h utils_v2.o train.o

utils_v2.o : utils_v2.h utils_v2.c

clean:
	rm -f *.o
	
sweep: clean
	rm -f $(PRG)
	ipcrm -a
