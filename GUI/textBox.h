/*
 * élément de l'interface graphique utilisateur: la saisie de texte
 */
#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

typedef struct
{
    SDL_Texture* texture;
    SDL_Rect rect;
    SDL_Rect maxRect; // cadre noir pour délimiter la zone de saisie

    SDL_Rect rBar; // rectangle de la barre clignotante

    bool select; // si la text box capture la saisie et affiche la bare clignotante
    
    char text[100];
    int maxcar; // nombre maximum de caractére
    int wLettre; // largeur d'une lettre
} TextBox;

TextBox createTextBox(char str[],int x,int y,int w,int h,int maxcar,bool arg0); // arg0: selected or not by default, h et w dimenssion de chaque lettre
void updateTextBox(TextBox* ptr);
void inputTextBox(TextBox* ptr,SDL_Event *event); // si select==true gére la saisie de caractères
void inputPassBox(TextBox* ptr,SDL_Event *event); // afficher des étoiles
void freeTextBox(TextBox *img);
void renderTextBox(TextBox *img);

#endif
