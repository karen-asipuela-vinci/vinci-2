#include <CUnit/Basic.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "utils_v1.h"
#include "messages.h"

void test_spoll(void)
{
    int pipefd[2];
    struct pollfd fds[1];

    // Créer un pipe
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Écrire dans le pipe
    write(pipefd[1], "test", 4);

    // Configurer la structure pollfd
    fds[0].fd = pipefd[0];
    fds[0].events = POLLIN;

    // Appeler spoll
    int ret = spoll(fds, 1, 0);

    // Vérifier que spoll renvoie 1 (un descripteur de fichier est prêt à être lu)
    CU_ASSERT_EQUAL(ret, 1);

    // Vérifier que POLLIN est défini pour le descripteur de fichier
    CU_ASSERT(fds[0].revents & POLLIN);

    // Fermer le pipe
    close(pipefd[0]);
    close(pipefd[1]);
}

int main()
{
    CU_pSuite pSuite = NULL;

    /* initialiser le registre de tests de CUnit */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* ajouter une suite au registre */
    pSuite = CU_add_suite("spoll_test_suite", 0, 0);
    if (NULL == pSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* ajouter le test à la suite */
    if ((NULL == CU_add_test(pSuite, "test_spoll", test_spoll)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Exécuter tous les tests
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return CU_get_error();
}