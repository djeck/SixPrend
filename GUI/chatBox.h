#ifndef CHATBOX_H
#define CHATBOX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>
#include "text.h"
#include "textBox.h"

#define NB_MSG 3
#define DY 30 // espace entre chaque rangée

typedef struct
{
  
  SDL_Rect rect; // X, Y, L and W for all the chat
  Text messages[NB_MSG];
  char text[NB_MSG][100];//chaques messages de %messages
  TextBox input; // user input
    
} ChatBox;

ChatBox createChatBox(int x,int y,int size);
void pushChatBox(ChatBox* ptr); // la chaine à rajouter est dans ptr->input.text
void inputChatBox(ChatBox* ptr,SDL_Event *event);
void freeChatBox(ChatBox *img);
void renderChatBox(ChatBox *img);

#endif
