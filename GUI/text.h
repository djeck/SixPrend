/*
 * élément de l'interface graphique utilisateur: le texte
 */
#ifndef TEXT_H
#define TEXT_H

#include "../Game/inc.h"

typedef struct
{
    SDL_Texture* texture;
    SDL_Rect rect;
    int size;
} Text;

Text createText(char str[],int x,int y,int size);
void updateText(Text* ptr,char str[]);
void freeText(Text *img);
void renderText(Text *img);
void setTextColor(int r,int g,int b);

#endif

