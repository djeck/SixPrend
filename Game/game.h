/*
 * Fichier correspondant à l'affichage et la gestion du jeu
 */

#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL_ttf.h>
#include <SDL_events.h>
#include <string.h>
#include "inc.h"
#define NB_CARD 104
#define HAND 10 // nombre de carte dans la main
#define POSHAND_X  20 // position de la premiere carte de la main selon X
#define POSHAND_Y 400 // position des cartes de la main selon Y
#define DECHAND 5 // ecart entre les carte de la main (selon X)
#define RANGEE 4 // nombre de rangee de cartes communes
#define CPRANGEE 6 // nombre de carte maximum par rangee
#define POSTABLE_X 10
#define POSTABLE_Y 20
#define DECRANGEE 5


static int table[RANGEE][CPRANGEE];
SDL_Rect posTable[RANGEE][CPRANGEE]; // la position de chaque carte posee sur la table
static int poignee[HAND]; // la main de l'utilisateur, contient le numero de la carte à afficher [1,104]
SDL_Rect posPoignee[HAND]; // la position de chaque carte da la main pour l'y afficher à l'écran
/*
 * ranger la main et calculer la position où sera rendu chaque image de la main
 */
void ordonner();
/*
 * Gestion des evenements spécifique au jeu
 */
void eventGame();
/*
 * Initialisation des ressources graphiques spécifique au jeu
 */
void initGameRender();
/*
 * dessine ressources graphiques spécifique au jeu
 */
void renderGame();
/*
 * Libere les ressources graphiques initialisees par initGameRender
 */
void freeGameRender();

#endif
