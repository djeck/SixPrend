/*
 * centralise les macros et inclusions utilisees dans plusieurs parties du projet
 */
#ifndef INC_H
#define INC_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "login.h"
#include "menu.h"
#include "game.h"
#include "mode.h"
#include "stat.h"

#define FILELOGIN "../media/login.txt"
#define BACKGROUNDPATH "../media/background.bmp" // fond d'ecran
#define FONTSIZE 256 // taille maximale chagé depuis le fichier de font
#define SCREEN_WIDTH 800 // largeur par default de la fenetre
#define SCREEN_HEIGHT 480 // hauteur par default de la fenetre
#define SIZESTR 21 // taille par default du nom
#define FONTPATH "../media/sixty.fon" // fichier de fnnt
#define FONTSIZE 256 // taille maximale chagé depuis le fichier de font
#define CLIGNE 500


TTF_Font* font; // initialisé par init()
SDL_Window * window;
SDL_Renderer * renderer;

typedef enum {none,login,menu,mode,stat,game,end} MainStep; // étapes principales du jeu

typedef struct
{
    SDL_Texture* texture;
    SDL_Rect rect;
    SDL_Rect rectCur; // rect du cursseur (pour la barre lors de saisie de texte par exemple)
    bool input; // sert à faire clignoter l'image (pour la barre lors de saisie de texte par exemple)
} Image;

typedef struct
{
    SDL_Texture* texture;
    SDL_Texture* textureselelct;
    SDL_Rect rect;
    bool select; // si l'untilisateur a selectionner cette image
} PickableImage;

// Etapes principale du jeu
MainStep globalStep;

/*
 * permet de mettre à jour l'etape principale
 * initialise et libere les ressources
 */
void changeStep(MainStep nextStep);

bool collisionWithMouse(SDL_Rect arg0,int mx,int my);

#endif
