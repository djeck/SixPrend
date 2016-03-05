/*
 * Composant de l'interface graphique ustilisateur: l'image
 */
#ifndef PICTURE_H
#define PICTURE_H

#include "../Game/inc.h"

typedef struct
{
    SDL_Texture* texture;
    SDL_Rect rect;
} Picture;

Picture createPicture(char path[],int x,int y,int size);
void freePicture(Picture *img);
void renderPicture(Picture *img);

#endif