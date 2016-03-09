/*
 * Fichier correspondant à l'affichage et la gestion de la page de parametre, avant l'acces au jeu
 */

#ifndef MODE_H
#define MODE_H

#include "../GUI/button.h"
#include "../GUI/picture.h"
#include "../GUI/chatBox.h"
#include "client.h"

/*
 * Gestion des evenements spécifique à la page de parametre
 */
void eventMode();
/*
 * Initialisation des ressources graphiques spécifique à la page de parametre
 */
void initModeRender();
/*
 * dessine ressources graphiques spécifique à la page de parametre
 */
void renderMode();
/*
 * Libere les ressources graphiques initialisees par initModeRender
 */
void freeModeRender();

#endif
