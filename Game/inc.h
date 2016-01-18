/*
 * centralise les macros et inclusions utilisees dans plusieurs parties du projet
 */
#ifndef INC_H
#define INC_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL/SDL.h>

#define SCREEN_WIDTH 800 // largeur par default de la fenetre
#define SCREEN_HEIGHT 480 // hauteur par default de la fenetre
#define SIZESTR 21 // taille par default du nom

#include "login.h"


typedef enum{none,login,menu,mode,stat,game,end} MainStep; // étapes principales du jeu

/*
 * stoque le nom de l'utilisateur bien identifié
 * defini pour les etapes menu, mode, stat,game
 * ne pas utiliser sinon
 */
char utilisateur[SIZESTR];

// Etapes principale du jeu
MainStep globalStep;

/*
 * permet de mettre à jour l'etape principale
 * initialise et libere les ressources
 */
void changeStep(MainStep nextStep);

#endif
