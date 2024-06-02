#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#include "utils_v1.h"

#define NAMEWIDTH 21
#define BUFSIZE 256

/* Handlers pour les fork */
static void exec_ls(void *arg)
{
  char *scriptName = arg;
  printf("\nls -l %s:\n", scriptName);
  sexecl("/bin/ls", "ls", "-l", scriptName, NULL);
}

static void exec_cat(void *arg)
{
  char *scriptName = arg;
  printf("\ncat %s:\n", scriptName);
  sexecl("/bin/cat", "cat", scriptName, NULL);
}

/* Main */
int main(int argc, char **argv)
{
  /* Lecture du nom du script au clavier */
  printf("Entrez le nom du script (max %d caractères)\n", NAMEWIDTH - 1);

  char scriptName[NAMEWIDTH];
  int nbCharRd = sread(0, scriptName, NAMEWIDTH);
  /* Remplacement du \n pour utilisation du format %s */
  scriptName[nbCharRd - 1] = 0;

  /* Création du fichier script avec permissions 700 */
  int fd = sopen(scriptName, O_WRONLY | O_TRUNC | O_CREAT, 0700);

  /* Faire un ls -l sur le nom du script créé */
  int c1 = fork_and_run1(exec_ls, scriptName);
  swaitpid(c1, NULL, 0);

  /* Ecriture du shebang dans le script */
  char *shebang = "#!/bin/bash\n";
  int szShebang = strlen(shebang);
  nwrite(fd, shebang, szShebang);

  /* Saisie du contenu du script */
  printf("\nSaisie du contenu de votre script (ctrl-d pour terminer).\n");
  char readBuffer[BUFSIZE];
  int nbrRead;
  while ((nbrRead = sread(0, readBuffer, BUFSIZE)) != 0)
  {
    nwrite(fd, readBuffer, nbrRead);
  }

  /* Libérer les ressources ! */
  sclose(fd);

  int c2 = fork_and_run1(exec_cat, scriptName);
  swaitpid(c2, NULL, 0);

  /* Exécution du script enregistré */
  printf("\n./%s:\n", scriptName);
  sexecl(scriptName, scriptName, NULL);
}

/*
Exercice sur les appels système : fork et exec
Vous allez écrire un programme interactif qui, au final :
- Saisira au clavier le nom d’un fichier script ;
- Créera le script avec les droits RWX------. Si le fichier existe,
    il sera réinitialisé.
- Exécutera un ls -l de ce fichier script via un exec ;
- Ecrira le shebang dans le script : #!/bin/bash
- Saisira au clavier, ligne par ligne, le contenu du script
    en l’écrivant en parallèle dans le fichier ;
- Exécutera ensuite un cat du contenu du script via un exec ;
- Exécutera finalement le script en question via un exec.

Suivez l’ordre des points ci-dessous en testant le caractère fonctionnel
de votre code de temps en temps.
a) Effectuez la lecture du nom du fichier script au clavier,
  à l’aide d’un appel système read, sans vérification particulière. Imposez un nom de maximum 20 caractères. Vous pouvez considérer que l’utilisateur ne fera pas de fausses manoeuvres.
b) Ouvrez le fichier en question en l’écrasant, ou créez-le si nécessaire.
c) A l’aide d’un fork/exec, effectuez un ls -l sur le nom du script.
d) A l’aide d’appels système read et write, lisez au clavier,
  ligne par ligne, le contenu du script en l’écrivant en parallèle
  dans le fichier créé.
e) A l’aide d’un fork/exec, effectuez un cat du contenu du script.
f) Libérez les ressources, puis exécutez le contenu du script.
g) Les affichages à l’écran peuvent être réalisés grâce à la fonction printf.
h) Très important : vous avez à votre disposition la librairie utils.
  utilisez celle-ci à bon escient pour vous faciliter le travail
  et augmenter la clarté du code !
*/