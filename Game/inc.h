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

#define BACKGROUNDPATH "./media/background.bmp" // fond d'ecran
#define OKPATH "./media/ok.bmp"
#define NOPATH "./media/no.bmp"
#define ROBOTPATH "./media/robot.bmp"
#define FONTSIZE 256 // taille maximale chagé depuis le fichier de font
#define SCREEN_WIDTH 800 // largeur par default de la fenetre
#define SCREEN_HEIGHT 480 // hauteur par default de la fenetre
#define SIZESTR 21 // taille par default du nom
#define FONTPATH "./media/sixty.fon" // fichier de fnnt
#define CLIGNE 500

#include <SDL2/SDL_ttf.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "login.h"
#include "menu.h"
#include "game.h"
#include "mode.h"
#include "stat.h"

TTF_Font* font; // initialisé par init()

typedef enum{none,login,menu,mode,stat,game,end} MainStep; // étapes principales du jeu

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
  bool select;
} PickableImage;

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

Image createText(char str[],int x,int y,int size,bool input);
void updatePickableText(PickableImage* ptr,char str[], int x, int y, int size);
void updateText(Image* ptr,char str[],int x,int y,int size);
PickableImage createPickableText(char str[],int x,int y,int size);
void setTextColor(int r,int g,int b);
Image createPicture(char* path, int x, int y,int size);
bool collisionWithMouse(SDL_Rect arg0,int mx,int my);
void renderImage(Image img);
void renderIn(Image img,SDL_Rect rect);
void freeImage(Image img);
void renderPickableImage(PickableImage img);
void freePickableImage(PickableImage img);

#endif
