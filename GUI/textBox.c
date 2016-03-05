#include "textBox.h"

extern SDL_Renderer *renderer;
extern TTF_Font* font;

static SDL_Color color = {0,0,0};

TextBox createTextBox(char str[],int x,int y,int size)
{
    SDL_Surface *stext;
    TextBox img;
    img.select=false;
    img.rect.x = x;
    img.rect.y = y;
    strcpy(img.text,str);
    
    if(!font)
        printf("createTextBox: font non charge\n");

    if(strlen(str)==0)
    {
        printf("createTextBox: chaine vide\n");
	str=" ";
        stext = TTF_RenderText_Solid(font,str,color);
    }
    else
    {
        stext = TTF_RenderText_Solid(font,str,color);
    }
    if (! stext )
    {
        printf("createTextBox: impossible de cree la surface du text %s\n",TTF_GetError());
        img.texture=NULL;
        changeStep(end);
        return img;
    }

    img.texture = SDL_CreateTextureFromSurface(renderer,stext);
    if (! img.texture )
    {
        printf("createTextBox: impossible de cree la texture du text\n");
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

void updateTextBox(TextBox* ptr)
{
    if(ptr->texture)
    {
	freeTextBox(*ptr);
        *ptr = createPickableText(ptr->text,ptr->rect.x,ptr->rect.y,ptr->size);
    }
    else
        printf("updateText: texture non initialisee ne peut pas etre mis à jour\n");
}

void freeTextBox(TextBox *img)
{
    SDL_DestroyTexture(*img.texture);
}

static Uint32 timer=0;
void renderTextBox(TextBox *img)
{
  SDL_RenderCopy(renderer,img.texture,NULL,&img.rect);
    if(img.input && SDL_GetTicks()-timer > CLIGNE)
    {
        if(SDL_GetTicks()-timer > 2*CLIGNE)
            timer=SDL_GetTicks();
        SDL_RenderFillRect(renderer, &img->rBar);
        //SDL_RenderDrawRect(renderer,&rect);
    }
}
void inputTextBox(TextBox* ptr,SDL_Event *event)
{
 if(ptr->select && event->type == SDL_TEXTINPUT && strlen(ptr->text)<100-1)
 {
   strcat(ptr->text, event->text.text);
   updateTextBox(ptr);
 }
}

