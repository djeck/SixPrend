/*
 * Fichier correspondant à l'affichage des statistiques
 */

#ifndef STAT_H
#define STAT_H

#include <SDL2/SDL_ttf.h>
#include <SDL_events.h>
#include <string.h>
#include "inc.h"

/*
 * Gestion des evenements spécifique au statistiques
 */
void eventStat();
/*
 * Initialisation des ressources graphiques spécifique au statistiques
 */
void initStatRender();
/*
 * dessine ressources graphiques spécifique au statistiques
 */
void renderStat();
/*
 * Libere les ressources graphiques initialisees par initStatRender
 */
void freeStatRender();

#endif
