/*
 * Fichier correspondant à l'affichage et la gestion du login dun jeu
 */

#ifndef LOGIN_H
#define LOGIN_H

#define BACKGROUNDPATH "./media/background.bmp" // fond d'ecran
#define FONTPATH "./media/sixty.fon" // fichier de fnnt
#define FONTSIZE 256 // taille maximale chagé depuis le fichier de font

#include <SDL2/SDL_ttf.h>
#include "inc.h"

/*
 * Gestion des evenements spécifique au login
 * agis sur la variable globale terminer
 */
void eventLogin();
/*
 * Initialisation des ressources graphiques spécifique au rendu du login
 * necessite la variable renderer
 */
void initLoginRender();
/*
 * Met à jour la texture du texte avec la chaine de charactere str
 */
void updateText(char str[]);
/*
 * dessine ressources graphiques spécifique au rendu du login
 * necessite la variable renderer
 */
void renderLogin();
/*
 * Libere les ressources graphiques initialisees par initLoginRender
 */
void freeLoginRender();

#endif
