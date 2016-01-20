#include "stat.h"

static PickableImage choixBack;
static Image Background;

void eventStat()
{
  SDL_Event event;
	while (SDL_PollEvent(&event))
	{
	  if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT )
	  {
	    if(collisionWithMouse(choixBack.rect,event.button.x,event.button.y))
	    {
	      changeStep(menu);
	    }
	      
	  }
	  else if( event.type == SDL_MOUSEMOTION )
	  {
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

void initStatRender()
{
	
	Background = createPicture(BACKGROUNDPATH,0,0,1);
	
	choixBack = createPickableText("Return",100,500,8);
	
	renderinitialised=1;
}
void renderStat()
{
	if(renderinitialised==0)
		return;
	renderImage(Background);
	renderPickableImage(choixBack);
}

void freeStatRender()
{
	if(renderinitialised==0)
	{
	  printf("freeStatRender: ne peut pas liberer les ressources car elles n'ont pas etaient inititialisé\n");
		return;
	}
	renderinitialised=0;
	freePickableImage(choixBack);
	freeImage(Background); // Libération de la mémoire associée à la texture

	printf("freeStatRender: liberation des ressources\n");
}