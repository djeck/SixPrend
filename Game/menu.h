/**
 * \file menu.h
 * \brief Fichier correspondant à l'affichage et la gestion du menu du jeu
 * \author Aubin Detrez
 *
 */
#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_events.h>
#include <string.h>
#include "../GUI/picture.h"
#include "../GUI/button.h"
#include "inc.h"

/**
 * \fn void eventMenu()
 * \brief Gestion des evenements spécifique au menu
 */
void eventMenu();
/**
 * \fn void initMenuRender()
 * \brief Initialisation des ressources graphiques spécifique au rendu du menu
 */
void initMenuRender();
/**
 * \fn void renderMenu()
 * \brief dessine ressources graphiques spécifique au rendu du menu
 */
void renderMenu();
/**
 * \fn void freeMenuRender()
 * \brief Libere les ressources graphiques initialisees par initMenuRender
 */
void freeMenuRender();

#endif
