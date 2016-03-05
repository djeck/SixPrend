#include "text.h"

extern SDL_Renderer *renderer;
extern TTF_Font* font;

static SDL_Color color = {0,0,0};

void setTextColor(int r, int g, int b)
{
    color.r=r;
    color.g=g;
    color.b=b;
}

Text createText(char str[],int x,int y,int size)
{
    SDL_Surface *stext;
    Text img;
    img.rect.x = x;
    img.rect.y = y;
    // taille automatique

    if(!font)
        printf("getText: font non charge\n");

    if(strlen(str)==0)
    {
        printf("getText: chaine vide\n");
        stext = TTF_RenderText_Solid(font," ",color);
    }
    else
    {
        stext = TTF_RenderText_Solid(font,str,color);
    }
    if (! stext )
    {
        printf("getText: impossible de cree la surface du text\n");
        img.texture=NULL;
        changeStep(end);
        return img;
    }
    img.texture = SDL_CreateTextureFromSurface(renderer,stext);
    if (! img.texture )
    {
        printf("getText: impossible de cree la texture du text\n");
        img.texture=NULL;
        changeStep(end);
        return img;
    }

    img.size=size;
    img.rect.h = stext->h/size;
    img.rect.w = stext->w/size;
    SDL_FreeSurface(stext);
    return img;
}

void updateText(Text* ptr,char str[])
{
    if(ptr->texture)
    {
	SDL_DestroyTexture(ptr->texture);
        *ptr = createText(str,ptr->rect.x,ptr->rect.y,ptr->size);
    }
    else
        printf("updateText: texture non initialisee ne peut pas etre mis à jour\n");
}

void freeText(Text *img)
{
    SDL_DestroyTexture(img->texture);
}

static Uint32 timer=0;
void renderText(Text *img)
{
  SDL_RenderCopy(renderer,img->texture,NULL,&img->rect);
}

