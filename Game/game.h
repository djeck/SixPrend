/*
 * Fichier correspondant à l'affichage et la gestion du jeu
 */
/**
 * \file game.h
 * \brief interface graphique du jeu
 * \author Aubin Detrez
 *
 * affichage des informations depuis les données du serveur
 *
 */
#ifndef GAME_H
#define GAME_H

#include "inc.h"
#include "../GUI/button.h"
#include "../GUI/card.h"
#include "../GUI/text.h"
#include "../GUI/picture.h"

#define SIZESTR 21
#define MAXJOUEUR 10 // nombre maximal de joueur dans une partie
#define NB_CARD 104 // nombre total de cartes différentes
#define HAND 10 // nombre de carte dans la main
#define POSHAND_X  20 // position de la premiere carte de la main selon X
#define POSHAND_Y 400 // position des cartes de la main selon Y
#define DECHAND 5 // ecart entre les carte de la main (selon X)
#define RANGEE 4 // nombre de rangee de cartes communes
#define CPRANGEE 6 // nombre de carte maximum par rangee
#define POSTABLE_X 10 // position de la pemière carte de la table selon X
#define POSTABLE_Y 20 // position de la pemière carte de la table selon Y
#define DECRANGEE 7 // décalage entre les rangées
#define POSJOUEUR_X 800 // position X des informations sur les joueurs
#define POSJOUEUR_Y 5 // position selon Y de la premiére information sur les joueurs
#define SIZEJOUEUR 60 // taille réservé à l'affichage de chaque joueur

/**
* \struct Joueur
* \brief Objet positionnement et valeurs de données sur chaque joueur
*
* permet de savoir quoi afficher et ou pour les score et joueurs
*
*/
typedef struct {
    char nom[SIZESTR];  /*!< chaine de caractère nom du joueur */
    int tete; /*!< nombre de tête de boeuf (score) du joueur*/
    SDL_Rect rect; /*!< positionnement à l'écran de ces informations*/
} Joueur;

/**
 * \fn void updateJoueur()
 * \brief met à jour les donnees à afficher pour chaque joueur
 */
void updateJoueur();

/**
 * \fn void createJoueur()
 * \brief creer les donnees à afficher pour chaque joueur
 * se sert de données du tableau joueurs (cf game.c)
 */
void createJoueur();

/**
 * \fn void ordonner()
 * \brief ranger la main
 * le tableau représentant la main du joueur est 'poignee' (cf game.c)
 */
void ordonner();
/**
 * \fn void eventGame()
 * \brief Gestion des evenements spécifique au jeu
 */
void eventGame();
/**
 * \fn void initGameRender()
 * \brief Initialisation des ressources graphiques spécifique au jeu
 */
void initGameRender();
/**
 * \fn void renderGame()
 * \brief dessine ressources graphiques spécifique au jeu
 */
void renderGame();
/**
 * \fn void freeGameRender()
 * \brief Libere les ressources graphiques initialisees par initGameRender
 */
void freeGameRender();

#endif
