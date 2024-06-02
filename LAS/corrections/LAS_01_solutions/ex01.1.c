#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define NUMBER_OF_ITERATIONS 10000000
#define FILENAME_FWRITE "numbers_fwrite.bin"
#define FILENAME_WRITE "numbers_write.bin"

// déclaration des fonctions
void test_write_with_fwrite(char *output_filename, int number_of_iterations);
void test_write_with_write(char *output_filename, int number_of_iterations);
void usage();

// fonction principale
int main(int argc, char *argv[])
{
    // vérifie si le nombre d'arguments est correct
    if (argc != 2)
    {
        usage();
    }

    // si l'argument est fwrite, exécute le test avec fwrite
    if (strcmp(argv[1], "fwrite") == 0)
    {
        printf("Test fwrite ... cela est rapide fwrite bufferise les I/O\n");
        test_write_with_fwrite(FILENAME_FWRITE, NUMBER_OF_ITERATIONS);
    }

    // si l'argument est write, exécute le test avec write
    if (strcmp(argv[1], "write") == 0)
    {
        printf("Test write ... cela va prendre du temps\n");
        test_write_with_write(FILENAME_WRITE, NUMBER_OF_ITERATIONS);
    }
    // si l'argument n'est pas valide, affiche l'usage
    else
    {
        usage();
    }
}

// fonction qui teste l'écriture avec fwrite
void test_write_with_fwrite(char *output_filename, int number_of_iterations)
{
    FILE *fout; // déclaration du fichier de sortie

    fout = fopen(output_filename, "wb"); // ouverture du fichier (wb = write binary)
    // on check si l'ouverture du fichier a réussi
    if (fout == NULL)
    {
        perror("Erreur lors de l'ouverture du fichier.\n");
        exit(10);
    }

    // boucle : on écrit dans le fichier
    for (int i = 0; i < number_of_iterations; i++)
    {
        if (fwrite(&i, sizeof(int), 1, fout) != 1)
        {
            perror("Erreur d'ecriture\n");
            exit(20);
        }
    }

    // on ferme le fichier et on check si la fermeture a réussi
    if (fclose(fout))
    {
        perror("Erreur lors de la fermeture du fichier ouvert en écriture\n");
        exit(13);
    }
}

// fonction qui teste l'écriture avec write
void test_write_with_write(char *output_filename, int number_of_iterations)
{
    int fd, nbCharWrite, ret; // déclaration du descripteur de fichier,
    // du nombre de caractères écrits
    // et du retour de la fonction close

    // ouverture du fichier
    // (O_WRONLY = ouverture en écriture, O_CREAT = création du fichier, O_TRUNC = troncature du fichier)
    fd = open(output_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        perror("Erreur lors de l'ouverture du fichier.\n");
        exit(10);
    }

    // boucle : on écrit dans le fichier
    for (int i = 0; i < number_of_iterations; i++)
    {
        nbCharWrite = write(fd, &i, 1);
        if (nbCharWrite != 1)
        {
            perror("Erreur d'ecriture\n");
            exit(20);
        }
    }

    // on ferme le fichier et on check si la fermeture a réussi
    ret = close(fd);
    if (ret == -1)
    {
        perror("Erreur lors de la fermeture du fichier ouvert en écriture\n");
        exit(13);
    }
}

// fonction qui affiche l'usage
void usage()
{
    fprintf(stderr, "Usage : time ./ex1 fwrite\n \ttime ./ex1 write\n");
    exit(EXIT_FAILURE);
}
