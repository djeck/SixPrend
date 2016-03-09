#include "../Game/inc.h"
#include "chatBox.h"

ChatBox createChatBox(int x, int y)
{
  ChatBox box;
  int i;
  box.rect.x = x;
  box.rect.y = y;
  box.rect.h = DY * (NB_MSG);
  box.rect.w = CHAT_W;
  box.callback = NULL;
  box.update = false;
  
  for(i=0;i<NB_MSG;i++)
  {
    strcpy(box.text[i],""); // on met des espaces pour que les surface associé aient une taille
    box.messages[i] = createText(box.text[i],box.rect.x,box.rect.y + DY * i,10);
  }
  box.input = createTextBox("",box.rect.x,box.rect.y + DY * NB_MSG,10,20,15,false);
  return box;
}

void pushChatBox(ChatBox* ptr)
{
  int i;
  for(i=0;i<NB_MSG-1;i++)
  {
    strcpy(ptr->text[i],ptr->text[i+1]);
    updateText(&ptr->messages[i],ptr->text[i]);
  }
  strcpy(ptr->text[NB_MSG-1],ptr->input.text);
  updateText(&ptr->messages[NB_MSG-1],ptr->text[NB_MSG-1]);
  ptr->input.text[0]='\0';
  updateTextBox(&ptr->input);
  ptr->update = false;
}

void inputChatBox(ChatBox* ptr, SDL_Event* event)
{
  if(ptr->input.select &&  event->type == SDL_KEYUP && (event->key.keysym.scancode == SDL_SCANCODE_RETURN || event->key.keysym.sym == SDLK_TAB) )
  {
    if(ptr->callback!=NULL)
      ptr->callback(ptr->input.text);
    pushChatBox(ptr);
  }
  else
    inputTextBox(&ptr->input,event);
}

void freeChatBox(ChatBox* img)
{
  int i;
  for(i=0;i<NB_MSG;i++)
    freeText(&img->messages[i]);
  freeTextBox(&img->input);
}

void renderChatBox(ChatBox* img)
{
  int i;
  if(img->update)
    pushChatBox(img);
  for(i=0;i<NB_MSG;i++)
    renderText(&img->messages[i]);
  renderTextBox(&img->input);
  SDL_RenderDrawRect(renderer,&img->rect);
}
