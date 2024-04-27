#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdlib.h>
#include "jeu.h"

// commande pour le lancer avec testUnit : gcc -o test_jeu test_jeu.c jeu.c
// puis lancer fichier créé : ./test_jeu

int randomIntBetween(int min, int max) {
    return min + rand() % (max - min + 1);
}

void test_calculateScore(void) {
    #define SIZE_BOARD 20

    int t1[SIZE_BOARD] = {20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1};
    printf("t1: %ls\n", t1);
    int expectedScore1 = 0; 
    int expectedScore2 = 3;

    int scoreCalculate = calculateScore(t1);
    // print score
    printf("scoreCalculate: %d\n", scoreCalculate);
    CU_ASSERT_EQUAL(scoreCalculate, expectedScore1);

    int t2[SIZE_BOARD] =  {20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,1,2,3};
    printf("t2: %ls\n", t2);
    int scoreCalculate2 = calculateScore(t2);
    printf("scoreCalculate2: %d\n", scoreCalculate2);
    CU_ASSERT_EQUAL(scoreCalculate2, expectedScore2);

}

void test_sortRanking(void) {
    Ranking ranking;
    ranking.nbPlayers = 4;
    strcpy(ranking.scores[0].pseudo, "Joueur 1");
    ranking.scores[0].score = 10;
    strcpy(ranking.scores[1].pseudo, "Joueur 2");
    ranking.scores[1].score = 20;
    strcpy(ranking.scores[2].pseudo, "Joueur 3");
    ranking.scores[2].score = 30;
    strcpy(ranking.scores[3].pseudo, "Joueur 4");
    ranking.scores[3].score = 40;

    sortRanking(&ranking);

    CU_ASSERT_STRING_EQUAL(ranking.scores[0].pseudo, "Joueur 4");
    CU_ASSERT_EQUAL(ranking.scores[0].score, 40);
    CU_ASSERT_STRING_EQUAL(ranking.scores[1].pseudo, "Joueur 3");
    CU_ASSERT_EQUAL(ranking.scores[1].score, 30);
    CU_ASSERT_STRING_EQUAL(ranking.scores[2].pseudo, "Joueur 2");
    CU_ASSERT_EQUAL(ranking.scores[2].score, 20);
    CU_ASSERT_STRING_EQUAL(ranking.scores[3].pseudo, "Joueur 1");
    CU_ASSERT_EQUAL(ranking.scores[3].score, 10);

}

int main() {
   CU_initialize_registry();

   CU_pSuite suite = CU_add_suite("calculateScore_test", 0, 0);

   CU_add_test(suite, "test_calculateScore", test_calculateScore);
   CU_add_test(suite, "test_sortRanking", test_sortRanking);

   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();

   return 0;
}
