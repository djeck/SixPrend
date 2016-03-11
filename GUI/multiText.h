#ifndef MULTITEXT_H
#define MULTITEXT_H

#include <stdbool.h>
#include <string.h>
#include "text.h"
#define NB_LINE 10

typedef struct
{
  Text messages[NB_LINE];
  char text[NB_LINE][100];//chaques messages de %messages
  bool update; // pour une mise à jour de messages avec text dans renderMultiText
} MultiText;

MultiText createMultiText(int x,int y);
void pushMultiText(MultiText* ptr,char *msg);
void freeMultiText(MultiText *img);
void renderMultiText(MultiText *img);

#endif
