#include "mode.h"

static PickableImage choixQuit;
static PickableImage choixBack;
static Image Background;

void eventMode()
{
  SDL_Event event;
	while (SDL_PollEvent(&event))
	{
	  if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT )
	  {
	    if(collisionWithMouse(choixQuit.rect,event.button.x,event.button.y))
	    {
	      changeStep(end);
	    }
	    if(collisionWithMouse(choixBack.rect,event.button.x,event.button.y))
	    {
	      changeStep(menu);
	    }
	      
	  }
	  else if( event.type == SDL_MOUSEMOTION )
	  {
	      choixQuit.select=collisionWithMouse(choixQuit.rect,event.motion.x,event.motion.y);
	      choixBack.select=collisionWithMouse(choixBack.rect,event.motion.x,event.motion.y);
	  }
		switch(event.type)
		{
			case SDL_QUIT:
				changeStep(end);
			break;
		}
	}
}

static int renderinitialised = 0;

void initModeRender()
{
	
	Background = createPicture(BACKGROUNDPATH,0,0,1);
	
	choixQuit = createPickableText("Exit",400,500,5);
	choixBack = createPickableText("Return",100,450,5);
	
	renderinitialised=1;
}
void renderMode()
{
	if(renderinitialised==0)
		return;
	renderImage(Background);
	renderPickableImage(choixQuit);
	renderPickableImage(choixBack);
}

void freeModeRender()
{
	if(renderinitialised==0)
	{
	  printf("freeModeRender: ne peut pas liberer les ressources car elles n'ont pas etaient inititialisé\n");
		return;
	}
	renderinitialised=0;
	freePickableImage(choixQuit);
	freePickableImage(choixBack);
	freeImage(Background); // Libération de la mémoire associée à la texture

	printf("freeModeRender: liberation des ressources\n");
}