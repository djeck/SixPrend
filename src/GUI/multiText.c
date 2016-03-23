#include "multiText.h"
#define DY 30 // espace entre chaque rangée

MultiText createMultiText(int x,int y)
{
  MultiText box;
  int i;
  box.update = false;
  box.initialised = false;

  for(i=0;i<NB_LINE;i++)
  {
    strcpy(box.text[i],"");
    box.messages[i] = createText(box.text[i],x,y + DY * i,10);
  }
  return box;
}
void pushMultiText(MultiText* ptr,char *msg)
{
  int i;
  for(i=0;i<NB_LINE-1;i++)
  {
    strcpy(ptr->text[i],ptr->text[i+1]);
    updateText(&ptr->messages[i],ptr->text[i]);
  }
  strcpy(ptr->text[NB_LINE-1],msg);
  updateText(&ptr->messages[NB_LINE-1],ptr->text[NB_LINE-1]);
}
void updateMultiText(MultiText* ptr)
{
  int i;
  for(i=0;i<NB_LINE;i++)
  {
    updateText(&ptr->messages[i],ptr->text[i]);
  }
  ptr->update = false;
}
void inputMultiText(MultiText* ptr,SDL_Event *event)
{
    int i;
  if(ptr->initialised && event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT )
  {
      for(i=0;i<NB_LINE;i++)
       if(strlen(ptr->text[i])>0 && collisionWithMouse(ptr->messages[i].rect,event->button.x,event->button.y))
            ptr->callback(ptr->text[i]);
  }
}
void freeMultiText(MultiText *img)
{
  int i;
  for(i=0;i<NB_LINE;i++)
    freeText(&img->messages[i]);
}
extern SDL_Renderer* renderer;
void renderMultiText(MultiText *img)
{
  int i;
  if(img->update)
    updateMultiText(img);
  for(i=0;i<NB_LINE;i++)
  {
    renderText(&img->messages[i]);
    if(strlen(img->text[i])>0)
        SDL_RenderDrawRect(renderer,&img->messages[i].rect);
  }
}
