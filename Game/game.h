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
