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
#include "menu.h"

TTF_Font* font; // initialisé par init()

typedef enum{none,login,menu,mode,stat,game,end} MainStep; // étapes principales du jeu

typedef struct
{
  SDL_Texture* texture;
  SDL_Rect rect;
} Image;


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
Image getText(char str[],int x,int y,int size);
void setTextColor(int r,int g,int b);
Image getPicture(char* path, int x, int y,int size);

#endif
