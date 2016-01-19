/*
 * Fichier correspondant à l'affichage et la gestion de la page de parametre, avant l'acces au jeu
 */

#ifndef MODE_H
#define MODE_H

#include <SDL2/SDL_ttf.h>
#include <SDL_events.h>
#include <string.h>
#include "inc.h"

/*
 * Gestion des evenements spécifique à la page de parametre
 */
void eventMode();
/*
 * Initialisation des ressources graphiques spécifique à la page de parametre
 * necessite la variable renderer
 */
void initModeRender();
/*
 * dessine ressources graphiques spécifique à la page de parametre
 * necessite la variable renderer
 */
void renderMode();
/*
 * Libere les ressources graphiques initialisees par initModeRender
 */
void freeModeRender();

#endif
