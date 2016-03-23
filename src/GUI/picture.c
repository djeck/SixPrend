#include "picture.h"

extern SDL_Renderer *renderer;

Picture createPicture(char path[],int x,int y,int size)
{
    Picture img;
    img.rect.x = x;
    img.rect.y =y;
    printf("createPicture: loading picture %s\n",path);
    SDL_Surface* surface = SDL_LoadBMP(path);
    if ( !surface )
    {
        printf("createPicture: impossible de creer le sprite de l'image de fond, impossible d'ouvrir le fichier\n");
        img.texture = NULL;
        changeStep(end);
        return img;
    }
    img.texture = SDL_CreateTextureFromSurface(renderer,surface); // Préparation du sprite
    if (! img.texture )
    {
        printf("createPicture: impossible de cree la texture de l'image de fond\n");
        img.texture = NULL;
        changeStep(end);
        return img;
    }
    img.rect.h = surface->h/size;
    img.rect.w = surface->w/size;
    SDL_FreeSurface(surface);
    return img;
}

void freePicture(Picture *img)
{
  
  SDL_DestroyTexture(img->texture);
}

void renderPicture(Picture *img)
{
  SDL_RenderCopy(renderer,img->texture,NULL,&img->rect);
}