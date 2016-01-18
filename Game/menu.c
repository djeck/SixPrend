#include "menu.h"

void eventMenu()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
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

extern SDL_Renderer* renderer;
static int renderinitialised = 0;

static Image Background;
static Image imgtext;


void initMenuRender()
{
	
	Background = getPicture(BACKGROUNDPATH,0,0,1);
	
	imgtext = getText("hello world!",100,200,5);
	
	renderinitialised=1;
}

void renderMenu()
{
	if(renderinitialised==0)
		return;
	SDL_RenderCopy(renderer,Background.texture,NULL,&Background.rect); // Copie du sprite grâce au SDL_Renderer
	SDL_RenderCopy(renderer,imgtext.texture,NULL,&imgtext.rect);
}

void freeMenuRender()
{
	if(renderinitialised==0)
	{
	  printf("freeMenuRender: ne peut pas liberer les ressources car elles n'ont pas etaient inititialisé\n");
		return;
	}
	renderinitialised=0; // pour etre sur que on ne dessine pas avec les ressources qui ne sont plus disponiblent
	SDL_DestroyTexture(imgtext.texture);
	SDL_DestroyTexture(Background.texture); // Libération de la mémoire associée à la texture

	printf("freeMenuRender: liberation des ressources\n");
}