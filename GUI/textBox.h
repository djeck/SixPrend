/*
 * élément de l'interface graphique utilisateur: la saisie de texte
 */
#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "../Game/inc.h"

typedef struct
{
    SDL_Texture* texture;
    SDL_Rect rect;

    SDL_Rect rBar; // rectangle de la barre clignotante

    bool select; // si la text box capture la saisie et affiche la bare clignotante
    int size;
    
    char text[100];
} TextBox;

TextBox createTextBox(char str[],int x,int y,int size,bool arg0); // arg0: selected or not by default
void updateTextBox(TextBox* ptr);
void inputTextBox(TextBox* ptr,SDL_Event *event); // si select==true gére la saisie de caractères
void inputPassBox(TextBox* ptr,SDL_Event *event); // afficher des étoiles
void freeTextBox(TextBox *img);
void renderTextBox(TextBox *img);

#endif
