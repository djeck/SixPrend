/*
 * Fichier correspondant à l'affichage et la gestion du menu du jeu
 */

#ifndef MENU_H
#define MENU_H

#define BACKGROUNDPATH "./media/background.bmp" // fond d'ecran
#define FONTPATH "./media/sixty.fon" // fichier de fnnt
#define FONTSIZE 256 // taille maximale chagé depuis le fichier de font

#include <SDL2/SDL_ttf.h>
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
 * Met à jour la texture du texte avec la chaine de charactere str
 */
void updateText(char str[]);
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
