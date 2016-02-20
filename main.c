/*
 *  Entrée du programme, comprend uniquement la fonction main
 *
 */

#include "Game/inc.h"
#include "Game/init.h"
#include "time.h"

extern SDL_Renderer *renderer;

int main(int argc, char ** argv)
{
    srand(time(NULL));
    
    printf("main: lancement du jeu\n");

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
            renderMenu();
            break;
        case mode:
            renderMode();
            break;
        case stat:
            renderStat();
            break;
        case game:
            renderGame();
            break;
        case end:
            break;
        default:
            printf("main: globalState non valide\n");
        }

        SDL_RenderPresent(renderer);

        SDL_Delay(1); // provisoire afin de ne pas utiliser tout le cpu

        switch(globalStep)
        {
        case login:
            eventLogin();
            break;
        case menu:
            eventMenu();
            break;
        case mode:
            eventMode();
            break;
        case stat:
            eventStat();
            break;
        case game:
            eventGame();
            break;
        case end:
            break;
        default:
            printf("main: globalState non valide\n");

        }
    }

    //free ressource
    printf("main: liberation des ressources\n");
    quit();// liberation des ressources communes
    printf("main: fin du jeu\n");
    return 0;
}
