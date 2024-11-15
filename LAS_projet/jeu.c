#include <stdio.h>
#include <string.h>
#include "jeu.h"
#include "utils_v1.h"
#include "score.h"
#include "player.h"

int points[] = {0, 1, 3, 5, 7, 9, 11, 15, 20, 25, 30, 35, 40, 50, 60, 70, 85, 100, 150, 300};

int *initializeBoard()
{
    static int board[SIZE_BOARD];

    for (int i = 0; i < SIZE_BOARD; i++)
    {
        board[i] = 0;
    }
    return board;
}

void displayBoard(int t[])
{

    for (int i = 0; i < SIZE_BOARD; i++)
    {
        printf("%2d ", i + 1);
    }
    printf("\n");

    for (int i = 0; i < SIZE_BOARD; i++)
    {
        printf("%2d ", t[i]);
    }
    printf("\n");
}

int placeTile(int t[], int p, int tuile)
{
    // decrementation de l'emplacement
    p--;

    while (t[p] != 0)
    {
        p++;
        if (p == SIZE_BOARD)
        {
            p = 0;
        }
    }
    t[p] = tuile;
    // on retourne la position de la tuile
    return p;
}

int *initializeTiles()
{
    static int tiles[NUMBER_OF_TILES];

    int currentPlace = 0;

    // ajoute toutes les tuiles de 1 à 31 (joker inclus)
    for (int i = 1; i < 32; i++)
    {
        tiles[currentPlace] = i;
        currentPlace++;
    }

    // ajoute les tuiles en double de 11 à 19
    for (int i = 11; i < 20; i++)
    {
        tiles[currentPlace] = i;
        currentPlace++;
    }

    return tiles;
}

int drawRandomTile(int tiles[])
{
    int randomTile = randomIntBetween(0, NUMBER_OF_TILES);

    // tant que la tuile est déjà tirée, on en tire une autre
    while (tiles[randomTile] == 0)
    {
        randomTile = randomIntBetween(0, NUMBER_OF_TILES);
    }

    // on récupère la tuile et on la retire du tableau en la mettant à 0
    int tile = tiles[randomTile];
    tiles[randomTile] = 0;

    return tile;
}

int calculateScore(int t[])
{
    int score = 0;
    int currentSequenceLength = 0;

    for (int i = 0; i < SIZE_BOARD - 1; i++)
    {
        if (t[i] <= t[i + 1] || t[i + 1] == 31 || (t[i] == 31 && t[i - 1] <= t[i + 1]))
        {
            currentSequenceLength++;
        }
        else
        {
            score += points[currentSequenceLength];
            currentSequenceLength = 0;
        }
    }

    score += points[currentSequenceLength];

    return score;
}
void displayScore(Ranking *ranking)
{
    if (ranking->nbPlayers <= 0 || ranking->nbPlayers > MAX_PLAYERS)
    {
        printf("Invalid number of players: %d\n", ranking->nbPlayers);
        return;
    }

    printf("first if passed\n");
    printf("Number of players: %d\n", ranking->nbPlayers);
    for (int i = 0; i < ranking->nbPlayers; i++)
    {
        printf("first for loop\n");
        if (ranking->scores[i].pseudo[strlen(ranking->scores[i].pseudo) - 1] != '\0')
        {
            printf("Player name is not properly null-terminated.\n");
            return;
        }
        printf("%d. %s : %d\n", i, ranking->scores[i].pseudo, ranking->scores[i].score);
    }
}

Ranking *sortRanking(Ranking *ranking)
{
    printf("Sorting ranking in jeu.c\n");
    Score temp;
    for (int i = 0; i < ranking->nbPlayers; i++)
    {
        for (int j = i + 1; j < ranking->nbPlayers; j++)
        {
            if (ranking->scores[i].score < ranking->scores[j].score)
            {
                temp = ranking->scores[i];
                ranking->scores[i] = ranking->scores[j];
                ranking->scores[j] = temp;
            }
        }
    }
    return ranking;
}
