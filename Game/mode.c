#include "mode.h"

static Button choixQuit;
static Button choixStart;
static Button choixBack;
static Picture Background;
static Button choixConnect;

static Text ipAsk;
static TextBox ipServer;

static Text connecting; //message de connection

static char ipText[100];

/*
 * GETIP le joueur saisie de l'ip du serveur, premiere étape et on y retourne quant on change l'ip du serveur
 * CONNECT connection en cour au serveur
 * SALLE le joueur choisi la salle à rejoindre ou à créer
 * READY tout choix ok, reste au client à cliquer sur game
 */
enum {GETIP=0, CONNECT=1, SALLE=2,READY=3} modeStep;

void eventMode()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
	inputTextBox(&ipServer,&event);
	inputButton(&choixQuit,&event);
	inputButton(&choixBack,&event);
	inputButton(&choixStart,&event);
	inputButton(&choixConnect,&event);
        
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
    strcpy(ipText,"127.0.0.1");
    Background = createPicture(BACKGROUNDPATH,0,0,1);
    
    choixQuit = createButton("Exit",400,550,8);
    choixBack = createButton("Return",100,550,8);
    choixStart = createButton("Start game",100,450,8);
    
    ipAsk = createText("Server IP",20,100,8);
    ipServer = createTextBox(ipText,150,100,8,true);
    choixConnect = createButton("Connect",400,100,8);
    
    connecting = createText("Connecting to server ...",150,300,6);
    void CQuit()
    {
      changeStep(end);
    }
    choixQuit.callback = &CQuit;
    void CMenu()
    {
      changeStep(menu);
    }
    choixBack.callback = &CMenu;
    void CGame()
    {
      changeStep(game);
    }
    choixStart.callback = &CGame;
    void CConnect()
    {
      modeStep=CONNECT;
    }
    choixConnect.callback = &CConnect;
    
    renderinitialised=1;
    modeStep=GETIP;
}
void renderMode()
{
    if(renderinitialised==0)
        return;
    renderPicture(&Background);
    
    renderText(&ipAsk);
    if(modeStep==CONNECT)
      renderText(&connecting);
    renderTextBox(&ipServer);
    renderButton(&choixConnect);
    renderButton(&choixQuit);
    renderButton(&choixBack);
    renderButton(&choixStart);
}

void freeModeRender()
{
    if(renderinitialised==0)
    {
        printf("freeModeRender: ne peut pas liberer les ressources car elles n'ont pas etaient inititialisé\n");
        return;
    }
    renderinitialised=0;
    freeButton(&choixConnect);
    freeButton(&choixQuit);// Libération de la mémoire associée aux textures
    freeTextBox(&ipServer);
    freeText(&ipAsk);
    freeText(&connecting);
    freeButton(&choixBack);
    freeButton(&choixStart);
    freePicture(&Background);

    printf("freeModeRender: liberation des ressources\n");
}
