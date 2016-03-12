/**
 * \file init.h
 * \brief Comprend L'initialisation de la SDL, et la liberation des ressources
 * \author Aubin Detrez
 */

#ifndef INIT_H
#define INIT_H

#include <SDL2/SDL_ttf.h>

#include "inc.h"

/**
 * \fn void init()
 * \brief initialisation des ressources 'globales'
 */
void init();

/**
 * \fn void quit()
 * \brief libere les ressources 'globales'
 */
void quit();

#endif
