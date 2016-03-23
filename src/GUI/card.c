#include "card.h"

SDL_Texture* cards[NB_CARD];

extern SDL_Renderer *renderer;

SDL_Texture* createTexture(char path[],int x,int y,int size)
{
    SDL_Texture* texture = NULL;
    SDL_Surface* surface = SDL_LoadBMP(path);
    if ( !surface )
    {
        printf("createTexture: impossible de creer le sprite de l'image de fond, impossible d'ouvrir le fichier %s\n",path);
        changeStep(end);
        return texture;
    }
    texture = SDL_CreateTextureFromSurface(renderer,surface); // Préparation du sprite
    if (! texture )
    {
        printf("createTexture: impossible de cree la texture de l'image de fond\n");
        texture = NULL;
        changeStep(end);
        return texture;
    }
    SDL_FreeSurface(surface);
    return texture;
}

void initCard()
{
  int i;
  char path[50];
  for(i=0; i<NB_CARD; i++) // chargement des ressources pour afficher toutes les cartes
    {
        sprintf(path,PATH_CARD,i+1);
        cards[i] = createTexture(path,0,0,1);
    }
}

void detroyCard()
{
  int i;
  for(i=0; i<NB_CARD; i++) // chargement des ressources pour afficher toutes les cartes
    SDL_DestroyTexture(cards[i]);
  printf("detroyCard: memory free\n");
}

void renderCard(Card* card)
{
  if(card->id>0 && card->id<=104)
  {
    SDL_RenderCopy(renderer,cards[card->id-1],NULL,&card->rect);
    if(card->selected)
      SDL_RenderDrawRect(renderer,&card->rect);
  }
}

void eventCard(SDL_Event* event, Card* card, void (*callback)(int))
{
  if( event->type == SDL_MOUSEMOTION )
  {
    card->selected=collisionWithMouse(card->rect,event->motion.x,event->motion.y);


  }
  if(event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT && collisionWithMouse(card->rect,event->button.x,event->button.y))
  {
    printf("eventCard callback used ...\n");
    (*callback)(card->id);
  }

}
