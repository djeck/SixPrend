#include "menu.h"

static Image Background;
static PickableImage choixJeu; // lancer le mode puis le jeu
static PickableImage choixStat;
static PickableImage choixQuit;

void eventMenu()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
	  if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT )
	  {
	    if(collisionWithMouse(choixJeu.rect,event.button.x,event.button.y))
	    {
	      changeStep(mode);
	    }
	    else if(collisionWithMouse(choixStat.rect,event.button.x,event.button.y))
	    {
	      changeStep(stat);
	    }
	    else if(collisionWithMouse(choixQuit.rect,event.button.x,event.button.y))
	    {
	      changeStep(end);
	    }
	      
	  }
	  else if( event.type == SDL_MOUSEMOTION )
	  {
	      choixJeu.select=collisionWithMouse(choixJeu.rect,event.motion.x,event.motion.y);
	      
	      choixQuit.select=collisionWithMouse(choixQuit.rect,event.motion.x,event.motion.y);

	      choixStat.select=collisionWithMouse(choixStat.rect,event.motion.x,event.motion.y);
	  }
		switch(event.type)
		{
			case SDL_QUIT:
				printf("eventLogin: event quit received\n");
				changeStep(end);
			break;
			case SDL_KEYUP:
			break;
		}
	}
}

static int renderinitialised = 0;

void initMenuRender()
{
	
	Background = createPicture(BACKGROUNDPATH,0,0,1);
	
	choixJeu = createPickableText("Play",100,150,5);
	choixStat = createPickableText("Statistic",100,210,5);
	choixQuit = createPickableText("Exit",100,270,5);
	
	renderinitialised=1;
}

void renderMenu()
{
	if(renderinitialised==0)
		return;
	renderImage(Background);
	renderPickableImage(choixJeu);
	renderPickableImage(choixStat);
	renderPickableImage(choixQuit);
}

void freeMenuRender()
{
	if(renderinitialised==0)
	{
	  printf("freeMenuRender: ne peut pas liberer les ressources car elles n'ont pas etaient inititialisé\n");
		return;
	}
	renderinitialised=0; // pour etre sur que on ne dessine pas avec les ressources qui ne sont plus disponiblent
	freePickableImage(choixJeu);
	freePickableImage(choixStat);
	freePickableImage(choixQuit);
	freeImage(Background); // Libération de la mémoire associée à la texture

	printf("freeMenuRender: liberation des ressources\n");
}