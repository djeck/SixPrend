#include "../Game/inc.h"
#include "textBox.h"

extern SDL_Renderer *renderer;
extern TTF_Font* font;

static SDL_Color color = {0,0,0};

TextBox createTextBox(char str[],int x,int y,int w,int h,int maxcar,bool arg0)
{
    SDL_Surface *stext;
    TextBox img;
    
    if(strlen(str)>maxcar)
      str[maxcar]='\0';
    
    img.maxcar = maxcar;
    img.select=arg0;
    
    img.wLettre = w;
    img.rect.x = x;
    img.rect.y = y;
    img.rect.h = h;
    img.rect.w = w * strlen(str); // largeur du mot

    img.maxRect.x = x;
    img.maxRect.y = y;
    img.maxRect.w = w * maxcar; // largeur maximal
    img.maxRect.h = h;
    
    strcpy(img.text,str);
    
    if(!font)
        printf("createTextBox: font non charge\n");

    if(strlen(str)==0)
    {
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
    
    img.rBar.h=img.rect.h;
    img.rBar.w=4;
    img.rBar.x=img.rect.x+img.rect.w;
    img.rBar.y=img.rect.y;

    SDL_FreeSurface(stext);
    return img;
}

void updateTextBox(TextBox* ptr)
{
    if(ptr->texture)
    {
	freeTextBox(ptr);
        *ptr = createTextBox(ptr->text,ptr->rect.x,ptr->rect.y,ptr->wLettre,ptr->rect.h,ptr->maxcar,ptr->select);
    }
    else
        printf("updateTextBox: texture non initialisee ne peut pas etre mise à jour\n");
}

void updatePassBox(TextBox* ptr)
{
  char buff[100],text[100];
  int i;
  if(ptr->texture)
    {
	freeTextBox(ptr);
	
	buff[0]='\0';
	for(i=0;i<strlen(ptr->text);i++)
	  strcat(buff,"*");
	strcpy(text,ptr->text);
	*ptr = createTextBox(buff,ptr->rect.x,ptr->rect.y,ptr->wLettre,ptr->rect.h,ptr->maxcar,ptr->select);
	strcpy(ptr->text,text);
    }
    else
        printf("updatePassBox: texture non initialisee ne peut pas etre mise à jour\n");
}

void freeTextBox(TextBox *img)
{
    SDL_DestroyTexture(img->texture);
}

static Uint32 timer=0;
void renderTextBox(TextBox *img)
{
  SDL_RenderCopy(renderer,img->texture,NULL,&img->rect);
  SDL_RenderDrawRect(renderer,&img->maxRect);
  
    if(img->select && SDL_GetTicks()-timer > CLIGNE)
    {
        if(SDL_GetTicks()-timer > 2*CLIGNE)
            timer=SDL_GetTicks();
        SDL_RenderFillRect(renderer, &img->rBar);
        //SDL_RenderDrawRect(renderer,&rect);
    }
}
void inputTextBox(TextBox* ptr,SDL_Event *event)
{
 if(ptr->select && strlen(ptr->text)<ptr->maxcar && event->type == SDL_TEXTINPUT && strlen(ptr->text)<100-1)
 {
   strcat(ptr->text, event->text.text);
   updateTextBox(ptr);
 }
 else if (ptr->select && event->type == SDL_KEYUP && (event->key.keysym.sym == SDLK_DELETE || event->key.keysym.sym == SDLK_BACKSPACE) && strlen(ptr->text)>0)
 {
   ptr->text[strlen(ptr->text)-1]='\0';
   updateTextBox(ptr);
 }
 else if( event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT)
  {
    ptr->select=collisionWithMouse(ptr->maxRect,event->button.x,event->button.y);
  }
}

void inputPassBox(TextBox* ptr,SDL_Event *event)
{
 if(ptr->select && strlen(ptr->text)<ptr->maxcar && event->type == SDL_TEXTINPUT && strlen(ptr->text)<100-1)
 {
   strcat(ptr->text, event->text.text);
   updatePassBox(ptr);
 }
 else if (ptr->select && event->type == SDL_KEYUP && (event->key.keysym.sym == SDLK_DELETE || event->key.keysym.sym == SDLK_BACKSPACE) && strlen(ptr->text)>0)
 {
   ptr->text[strlen(ptr->text)-1]='\0';
   updatePassBox(ptr);
 }
 else if( event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT)
  {
    ptr->select=collisionWithMouse(ptr->maxRect,event->button.x,event->button.y);
  }
}
