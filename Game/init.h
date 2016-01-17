/*
 * Comprend L'initialisation de la SDL, et la liberation des ressources
 */

#ifndef INIT_H
#define INIT_H

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "login.h"

/*
 * initialisation des ressources 'globales'
 */
void init();

/*
 * libere les ressources 'globales'
 */
void quit();

#endif
