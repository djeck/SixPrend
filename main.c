/*
 *  Entrée du programme, comprend uniquement la fonction main
 *
 */

#include "Game/inc.h"
#include "Game/init.h"
#include "Game/login.h"

int terminer = 0; // permet de mettre fin à la boucle de rendu

extern SDL_Renderer *renderer;

int main(int argc, char ** argv)
{


	init(); // initialisation des ressources communes à toute partie du jeu

	printf("main: initialisation des ressources graphiques du login\n");
	initLoginRender();

	printf("main: début de la boucle de rendu\n");
	while (terminer==0)
	{
		eventLogin(); // gestion des evenements specifique au login

		SDL_RenderClear(renderer);

		renderLogin(); // on dessine le login

		SDL_RenderPresent(renderer);
		SDL_Delay(1); // provisoire afin de ne pas utiliser tout le cpu
	}

	//free ressource
	printf("main: liberation des ressources\n");
	freeLoginRender(); // liberation des ressources du login

	quit();// liberation des ressources communes
	printf("main: fin du jeu\n");
	return 0;
}
