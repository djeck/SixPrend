#ifndef CHATBOX_H
#define CHATBOX_H

#include "text.h"
#include "textBox.h"

#define NB_MSG 3
#define DY 30 // espace entre chaque rangée
#define CHAT_W 200

typedef struct
{
  
  SDL_Rect rect; // X, Y, L and W for all messages
  Text messages[NB_MSG];
  char text[NB_MSG][100];//chaques messages de %messages
  TextBox input; // user input
  void (*callback)(char*); // optionel (appelé lors de la saisie d'un message par l'utilisateur
    
} ChatBox;

ChatBox createChatBox(int x,int y);
void pushChatBox(ChatBox* ptr); // la chaine à rajouter est dans ptr->input.text
void inputChatBox(ChatBox* ptr,SDL_Event *event);
void freeChatBox(ChatBox *img);
void renderChatBox(ChatBox *img);

#endif
