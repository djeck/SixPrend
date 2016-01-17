#include "Game/inc.h"
#include "Game/init.h"
#include "Game/login.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
int terminer = 0;
SDL_Window * window;
SDL_Renderer * renderer;


int main(int argc, char ** argv) 
{
	SDL_Event event;
  

	unsigned int frameLimit = SDL_GetTicks() + 16;
	SDL_Init(SDL_INIT_EVERYTHING);
  
	init();
  
	window = SDL_CreateWindow("SixPrend",
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            WINDOW_WIDTH, WINDOW_HEIGHT,
			    0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if(window == NULL || renderer == NULL)
		exit(1);
	
	printf("main: initialisation des ressources graphiques\n");
	initLoginRender();


	printf("main: début de la boucle de rendu\n");
	while (terminer==0) 
	{
		eventLogin();
	
		SDL_RenderClear(renderer);
		renderLogin();
		SDL_RenderPresent(renderer);
		SDL_Delay(1);
	}
	
	//free ressource
	printf("main: liberation des ressources\n");
	freeLoginRender();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	printf("main: fin du jeu\n");
	return 0;
}
