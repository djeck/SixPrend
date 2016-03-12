/**
 * \file mode.h
 * \brief Fichier correspondant à l'affichage et la gestion de la page de parametre, avant l'acces au jeu
 * \author Aubin Detrez
 *
 */
#ifndef MODE_H
#define MODE_H

#include "../GUI/button.h"
#include "../GUI/picture.h"
#include "../GUI/chatBox.h"
#include "client.h"
#include "../GUI/multiText.h"

/**
 * \fn void eventMode()
 * \brief Gestion des evenements spécifique à la page de parametre
 */
void eventMode();
/**
 * \fn void initModeRender()
 * \brief Initialisation des ressources graphiques spécifique à la page de parametre
 */
void initModeRender();
/**
 * \fn void renderMode()
 * \brief dessine ressources graphiques spécifique à la page de parametre
 */
void renderMode();
/**
 * \fn void freeModeRender()
 * \brief Libere les ressources graphiques initialisees par initModeRender
 */
void freeModeRender();

#endif
