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

void eventLogin();
void initLoginRender();
void updateText(char str[]);
void renderLogin();
void freeLoginRender();

#endif
