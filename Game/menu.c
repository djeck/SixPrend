#include "menu.h"

static Picture Background;
static Button choixJeu; // lancer le mode puis le jeu
static Button choixStat;
static Button choixQuit;

void eventMenu()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        inputButton(&choixJeu,&event);
        inputButton(&choixStat,&event);
        inputButton(&choixQuit,&event);

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

void CGameQuit() // quit game callback
{
    changeStep(end);
}
void CStat()
{
    changeStep(stat);
}
void CMode()
{
    changeStep(mode);
}
void initMenuRender()
{

    Background = createPicture(BACKGROUNDPATH,0,0,1);

    choixJeu = createButton("Play",100,150,5);
    choixStat = createButton("Statistic",100,210,5);
    choixQuit = createButton("Exit",100,270,5);

    choixJeu.callback = *CMode;
    choixQuit.callback = *CGameQuit;
    choixStat.callback = *CStat;

    renderinitialised=1;
}

void renderMenu()
{
    if(renderinitialised==0)
        return;
    renderPicture(&Background);
    renderButton(&choixJeu);
    renderButton(&choixStat);
    renderButton(&choixQuit);
}

void freeMenuRender()
{
    if(renderinitialised==0)
    {
        printf("freeMenuRender: ne peut pas liberer les ressources car elles n'ont pas etaient inititialisé\n");
        return;
    }
    renderinitialised=0; // pour etre sur que on ne dessine pas avec les ressources qui ne sont plus disponiblent
    freeButton(&choixJeu);
    freeButton(&choixStat);
    freeButton(&choixQuit);
    freePicture(&Background); // Libération de la mémoire associée à la texture

    printf("freeMenuRender: liberation des ressources\n");
}
