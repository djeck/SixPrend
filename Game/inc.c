/*
 * Comprend les fonctions communes à tout le jeu
 */
#include "inc.h"

void changeStep(MainStep nextStep)
{
    if(nextStep==globalStep || globalStep == end) // si il n'y a pas de changement ou que l'on s'apprêtait à quitter
        return; // on de charge pas les ressources

    switch(globalStep)
    {
    case login:
        freeLoginRender(); // liberation des ressources du login
        break;
    case menu:
        freeMenuRender();
        break;
    case mode:
        freeModeRender();
        break;
    case stat:
        freeStatRender();
        break;
    case game:
        freeGameRender();
        break;
    default:
        break;
    }

    switch(nextStep)
    {
    case login:
        initLoginRender();
        break;
    case menu:
        initMenuRender();
        break;
    case mode:
        initModeRender();
        break;
    case stat:
        initStatRender();
        break;
    case game:
        initGameRender();
        break;
    default:
        break;
    }
    globalStep=nextStep;
    printf("changeStep: changement d'etat effectue avec succes\n");
}

bool collisionWithMouse(SDL_Rect arg0,int mx,int my)
{
    SDL_GetMouseState(&mx, &my);
    bool haut=false,bas=false,gauche=false,droite=false;
    if(mx<arg0.x)
        gauche=true;
    if(mx>arg0.x+arg0.w)
        droite=true;
    if(my<arg0.y)
        haut=true;
    if(my>arg0.y+arg0.h)
        bas=true;
    if(gauche || droite || haut || bas)
        return false;
    return true;
}
