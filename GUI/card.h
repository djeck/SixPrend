/*
 * Composant de l'interface graphique ustilisateur: la carte
 */
#ifndef CARD_H
#define CARD_H

#include "../Game/inc.h"
#define NB_CARD 104
#define PATH_CARD "../media/%d.bmp"

typedef struct
{
    SDL_Rect rect;
    int id; // compris entre 0 et 104, 0 si non affiché
    bool selected; // met en évidence la carte selectionnée par le joueur
} Card;

void initCard();
void renderCard(Card* card);
void eventCard(SDL_Event *event,Card* card,void (*callback)(int));
void detroyCard();

#endif