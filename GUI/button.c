#include "button.h"

extern SDL_Renderer *renderer;
extern TTF_Font* font;

static SDL_Color color = {0,0,0};
static SDL_Color selColor = {255,0,0};

Button createButton(char str[],int x,int y,int size)
{
    SDL_Surface *stext;
    Button img;
    img.select=false;
    img.active=true;
    img.rect.x = x;
    img.rect.y = y;

    if(!font)
        printf("createButton: font non charge\n");

    if(strlen(str)==0)
    {
        printf("createButton: chaine vide\n");
	str=" ";
        stext = TTF_RenderText_Solid(font,str,color);
    }
    else
    {
        stext = TTF_RenderText_Solid(font,str,color);
    }
    if (! stext )
    {
        printf("createButton: impossible de cree la surface du text %s\n",TTF_GetError());
        img.texture=NULL;
        img.selTexture=NULL;
        changeStep(end);
        return img;
    }

    img.texture = SDL_CreateTextureFromSurface(renderer,stext);
    if (! img.texture )
    {
        printf("createButton: impossible de cree la texture du text\n");
        img.texture=NULL;
        img.selTexture=NULL;
        changeStep(end);
        return img;
    }
    SDL_FreeSurface(stext);

    stext = TTF_RenderText_Solid(font,str,selColor);
    if (! stext )
    {
        printf("createButton: impossible de cree la surface du text\n");
        img.selTexture=NULL; // img.texture est initialisee
        changeStep(end);
        return img;
    }

    img.selTexture = SDL_CreateTextureFromSurface(renderer,stext);
    if (! img.selTexture )
    {
        printf("createButton: impossible de cree la texture du text\n");
        img.selTexture=NULL; // img.texture est initialisee
        changeStep(end);
        return img;
    }

    img.rect.h = stext->h/size;
    img.rect.w = stext->w/size;
    SDL_FreeSurface(stext);
    return img;
}

void inputButton(Button* ptr, SDL_Event* event)
{
  if( event->type == SDL_MOUSEMOTION )
  {
    ptr->select=collisionWithMouse(ptr->rect,event->motion.x,event->motion.y);
  }
  if(event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT && collisionWithMouse(ptr->rect,event->button.x,event->button.y))
  {
       ptr->callback();
  }
}

void renderButton(Button* img)
{
    if(img->select)
        SDL_RenderCopy(renderer,img->selTexture,NULL,&img->rect);
    else
        SDL_RenderCopy(renderer,img->texture,NULL,&img->rect);
}

void freeButton(Button* img)
{
    SDL_DestroyTexture(img->texture);
    SDL_DestroyTexture(img->selTexture);
}
