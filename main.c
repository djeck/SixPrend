/*
 *  Entrée du programme, comprend uniquement la fonction main
 *
 */

#include "Game/inc.h"
#include "Game/init.h"

extern SDL_Renderer *renderer;

int main(int argc, char ** argv)
{


	init(); // initialisation des ressources communes à toute partie du jeu

	printf("main: initialisation des ressources graphiques du login\n");
	changeStep(login);

	printf("main: début de la boucle de rendu\n");
	while (globalStep!=end)
	{
		SDL_RenderClear(renderer);
		switch(globalStep)
		{
		  case login:
		    renderLogin();// on dessine le login
		  break;
		  case menu:
		    //renderMenu();
		  break;
		  case mode:
		    //renderMode();
		  break;
		  case stat:
		    //renderStat();
		  break;
		  case game:
		  //renderGame();
		  break;
		}
		
		SDL_RenderPresent(renderer);
		SDL_Delay(1); // provisoire afin de ne pas utiliser tout le cpu
		
		eventLogin(); // gestion des evenements specifique au login
	}

	//free ressource
	printf("main: liberation des ressources\n");
	quit();// liberation des ressources communes
	printf("main: fin du jeu\n");
	return 0;
}
