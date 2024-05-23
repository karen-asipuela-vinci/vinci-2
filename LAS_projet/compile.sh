#!/bin/bash

# ferme terminaux ouverts
killall xterm

#make clean
make clean

# Compile les fichiers source
make

# Ouvre un nouveau terminal et exécute la commande 'gcc -g server.c utils_v1.c network.c jeu.c -o server'
xterm -fa 'Monospace' -fs 12 -geometry 80x18+2660+178 -e "bash -c './run_gdb.exp gdb ./server 9501 test_files/tuiles1.txt; exec bash'" &

# Attends 5 secondes pour que le serveur démarre
sleep 2

# Ouvre un autre terminal et exécute la commande 'gcc -g client.c utils_v1.c network.c -o client'
xterm -fa 'Monospace' -fs 12 -geometry 80x18+3560+178 -e "bash -c './run_gdb_client.exp gdb ./client 9501 test_files/pos1.txt; exec bash'" &

xterm -fa 'Monospace' -fs 12 -geometry 80x18+3560+678 -e "bash -c './run_gdb_client.exp gdb ./client 9501 test_files/pos2.txt; exec bash'" &