#ifndef _JEU_H_
#define _JEU_H_

#include <stdio.h>

#define SIZE_BOARD 20
#define NUMBER_OF_TILES 40

/** 
 * Affiche le contenu de la grille de jeu
 * PRE: t un tableau de SIZE_BOARD entiers
 * POST: affiche le contenu de t sur la sortie standard
 */
void displayBoard(int t[]);
/** 
 * Donne une grille de jeu vide
 * POST: renvoie un tableau de SIZE_BOARD entiers initialisés à 0
 *  * RES: un tableau de SIZE_BOARD entiers
 */
int* initializeBoard();
/** 
 * Place une tuile sur la grille de jeu
 * PRE: t un tableau de SIZE_BOARD entiers
 *      p un entier
 *      tuile un entier entre 1 et 31
 * POST: place la tuile tuile sur la grille de jeu t à la position p, 
 * si la position est déjà occupée, la tuile est placée à la position
 *  suivante libre
 * RES: la position de la tuile sur la grille
 */
int placeTile(int t[], int p, int tuile);
/** 
 * Initialise les tuiles du jeu
 * POST: renvoie un tableau de NUMBER_OF_TILES entiers contenant les tuiles
 *  de 1 à 31 et les tuiles en double de 11 à 19
 * RES: un tableau de NUMBER_OF_TILES entiers
 */
int* initializeTiles();
/** 
 * Tire une tuile aléatoire dans celles encore disponibles
 * PRE: tuiles un tableau de NUMBER_OF_TILES entiers
 * POST: tire une tuile aléatoire dans tuiles et la retire du tableau
 * RES: un entier
 */
int drawRandomTile(int tuiles[]);
/** 
 * Calcule le score d'une grille de jeu
 * PRE: t un tableau de SIZE_BOARD entiers
 * POST: calcule le score de la grille de jeu t
 * RES: un entier
 */
int calculateScore(int t[]);

#endif
