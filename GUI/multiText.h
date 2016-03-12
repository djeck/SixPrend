#ifndef MULTITEXT_H
#define MULTITEXT_H

#include "../Game/inc.h"
#include "text.h"
#define NB_LINE 10

typedef struct
{
  Text messages[NB_LINE];
  char text[NB_LINE][100];//chaques messages de %messages
  bool update; // pour une mise à jour de messages avec text dans renderMultiText
  void (*callback)(char*); // appelle le callback lors d'un click sur le texte en parametre
  bool initialised; // on peut exploiter les données lors de clic
} MultiText;

MultiText createMultiText(int x,int y);
void pushMultiText(MultiText* ptr,char *msg);
void inputMultiText(MultiText* ptr,SDL_Event *event);
void freeMultiText(MultiText *img);
void renderMultiText(MultiText *img);

#endif
