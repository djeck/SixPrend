#include "Game/inc.h"
#include "Game/init.h"
#include "Game/login.h"

int terminer = 0;
extern SDL_Renderer *renderer;

int main(int argc, char ** argv) 
{
	SDL_Event event;
  
	init();
	
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
	quit();
	printf("main: fin du jeu\n");
	return 0;
}
