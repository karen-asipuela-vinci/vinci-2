#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define NUMBER_OF_ITERATIONS 10000000
#define FILENAME_FWRITE "numbers_fwrite.bin"
#define FILENAME_WRITE "numbers_write.bin"

void test_write_with_fwrite(char * output_filename, int number_of_iterations);
void test_write_with_write(char * output_filename, int number_of_iterations);
void usage();

int main(int argc, char* argv[]) {
    if (argc != 2){
       usage();
    }

    if (strcmp(argv[1],"fwrite") == 0)
    {
        printf("Test fwrite ... cela est rapide fwrite bufferise les I/O\n");
        test_write_with_fwrite(FILENAME_FWRITE, NUMBER_OF_ITERATIONS);
    }

    if (strcmp(argv[1],"write") == 0)
    {
        printf("Test write ... cela va prendre du temps\n");
        test_write_with_write(FILENAME_WRITE, NUMBER_OF_ITERATIONS);
    }
    else {
        usage();
    }
}

void test_write_with_fwrite(char * output_filename, int number_of_iterations)
{
 FILE *fout;

    fout = fopen(output_filename, "wb");
    if (fout == NULL) {
        perror("Erreur lors de l'ouverture du fichier.\n");
        exit(10);
    }

    for (int i = 0; i < number_of_iterations; i++) {
        if (fwrite(&i, sizeof(int), 1, fout) != 1) 
        {
            perror("Erreur d'ecriture\n");
            exit(20);
        }
    }

    if (fclose(fout)) {
      perror("Erreur lors de la fermeture du fichier ouvert en écriture\n");
      exit(13);
    }
}

void test_write_with_write(char * output_filename, int number_of_iterations)
{
    int fd, nbCharWrite, ret;
    fd = open(output_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Erreur lors de l'ouverture du fichier.\n");
        exit(10);
    }

    for (int i = 0; i < number_of_iterations; i++) {
        nbCharWrite = write(fd, &i, 1);
        if (nbCharWrite != 1) {
            perror("Erreur d'ecriture\n");
            exit(20);
        }
    }
    ret = close(fd);
    if (ret == -1)
    {
        perror("Erreur lors de la fermeture du fichier ouvert en écriture\n");
        exit(13);
    }
}

void usage()
{
    fprintf(stderr,"Usage : time ./ex1 fwrite\n \ttime ./ex1 write\n");
    exit(EXIT_FAILURE);
}


