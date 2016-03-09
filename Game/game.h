/*
 * Fichier correspondant à l'affichage et la gestion du jeu
 */

#ifndef GAME_H
#define GAME_H

#include "inc.h"
#include "../GUI/button.h"
#include "../GUI/card.h"
#include "../GUI/text.h"
#include "../GUI/picture.h"

#define MAXJOUEUR 10
#define NB_CARD 104
#define HAND 10 // nombre de carte dans la main
#define POSHAND_X  20 // position de la premiere carte de la main selon X
#define POSHAND_Y 400 // position des cartes de la main selon Y
#define DECHAND 5 // ecart entre les carte de la main (selon X)
#define RANGEE 4 // nombre de rangee de cartes communes
#define CPRANGEE 6 // nombre de carte maximum par rangee
#define POSTABLE_X 10
#define POSTABLE_Y 20
#define DECRANGEE 7
#define POSJOUEUR_X 800
#define POSJOUEUR_Y 5
#define SIZEJOUEUR 60 // taille réservé à l'affichage de chaque joueur

typedef struct {
    char nom[SIZESTR];
    int tete; // nombre de tête de boeuf
    SDL_Rect rect; // position à l'ecran de leur nom ...
} Joueur;

/*
 * met à jour les donnees à afficher pour chaque joueur
 */
void updateJoueur();
/*
 * creer les donnees à afficher pour chaque joueur
 */
void createJoueur();
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
