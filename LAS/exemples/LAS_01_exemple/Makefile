# Les options de compilation pour le compilateur gcc sont définies ici.
# -std=c11 : utilise la norme C11 du langage C.
# -pedantic : demande au compilateur d'appliquer strictement la norme C et d'émettre des avertissements si le code ne la respecte pas.
# -Wall : active tous les avertissements courants.
# -Wvla : avertit si le code utilise des tableaux de longueur variable, qui ne sont pas une fonctionnalité standard du C.
# -Werror : transforme tous les avertissements en erreurs.
# -D_DEFAULT_SOURCE : définit la macro _DEFAULT_SOURCE, qui active les fonctionnalités spécifiques à GNU/Linux dans les fichiers d'en-tête du système.
CFLAGS=-std=c11 -pedantic -Wall -Wvla -Werror -D_DEFAULT_SOURCE

# La cible 'exemple01' dépend des fichiers objet 'exemple01.o' et 'utils_v1.o'.
# La commande 'gcc $(CFLAGS) -o exemple01 exemple01.o utils_v1.o' est utilisée pour lier ces fichiers objet en un exécutable nommé 'exemple01'.
exemple01: exemple01.o utils_v1.o
	gcc $(CFLAGS) -o exemple01 exemple01.o utils_v1.o

# La cible 'exemple01.o' dépend du fichier source 'exemple01.c' et de l'en-tête 'utils_v1.h'.
# La commande 'gcc $(CFLAGS) -c exemple01.c' est utilisée pour compiler 'exemple01.c' en un fichier objet 'exemple01.o'.
exemple01.o: exemple01.c utils_v1.h
	gcc $(CFLAGS) -c exemple01.c

# La cible 'utils_v1.o' dépend du fichier source 'utils_v1.c' et de l'en-tête 'utils_v1.h'.
# La commande 'gcc $(CFLAGS) -c utils_v1.c' est utilisée pour compiler 'utils_v1.c' en un fichier objet 'utils_v1.o'.
utils_v1.o: utils_v1.c utils_v1.h
	gcc $(CFLAGS) -c utils_v1.c

# La cible 'clean' ne dépend d'aucun fichier. Elle est utilisée pour nettoyer le répertoire en supprimant les fichiers objet et les exécutables.
clean:
	rm -f *.o
	rm -f exemple01 test