#include "chatBox.h"

ChatBox createChatBox(int x, int y, int size)
{
  ChatBox box;
  int i;
  box.rect.x = x;
  box.rect.y = y;
  for(i=0;i<NB_MSG;i++)
  {
    strcpy(box.text[i],""); // on met des espaces pour que les surface associé aient une taille
    box.messages[i] = createText(box.text[i],box.rect.x,box.rect.y + DY * i,10);
  }
  box.input = createTextBox("",box.rect.x,box.rect.y + DY * NB_MSG,10,false);
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
  updateText(&ptr->messages,ptr->text[NB_MSG-1]);
  ptr->input.text[0]='\0';
  updateTextBox(&ptr->input);
}

void inputChatBox(ChatBox* ptr, SDL_Event* event)
{

}

void freeChatBox(ChatBox* img)
{

}

void renderChatBox(ChatBox* img)
{
  int i;
  for(i=0;i<NB_MSG;i++)
  {
    freeText(&img->messages[i]);
  }
  freeTextBox(&img->input);
}
