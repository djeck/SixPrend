/*
 * élément de l'interface graphique utilisateur: le bouton
 */
#ifndef BUTTON_H
#define BUTTON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../Game/inc.h"

typedef struct
{
    SDL_Texture* texture;
    SDL_Texture* selTexture; // texture pour le bouton selectionner
    SDL_Rect rect;

    bool active;
    bool select; // si la text box capture la saisie et affiche la bare clignotante
    int size;
    void (*callback)(void);
    
    char text[100];
} Button;

Button createButton(char str[],int x,int y,int size);
void inputButton(Button* ptr,SDL_Event *event); // si active == true gére les évenement
void renderButton(Button *img);
void freeButton(Button *img);


#endif