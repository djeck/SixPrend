/*
 * Fichier correspondant à l'affichage et la gestion du menu du jeu
 */

#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_events.h>
#include <string.h>
#include "inc.h"

/*
 * Gestion des evenements spécifique au menu
 */
void eventMenu();
/*
 * Initialisation des ressources graphiques spécifique au rendu du menu
 * necessite la variable renderer
 */
void initMenuRender();
/*
 * dessine ressources graphiques spécifique au rendu du menu
 * necessite la variable renderer
 */
void renderMenu();
/*
 * Libere les ressources graphiques initialisees par initMenuRender
 */
void freeMenuRender();

#endif
