#include "mode.h"

static PickableImage choixQuit;
static PickableImage choixStart;
static PickableImage choixBack;
static Image Background;

static PickableImage choixConnect;
static Image ipAsk;
static PickableImage ipServer;

static Image connecting; //message de connection

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
        if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT )
        {
            if(collisionWithMouse(choixQuit.rect,event.button.x,event.button.y))
            {
                changeStep(end);
            }
            else if(collisionWithMouse(choixBack.rect,event.button.x,event.button.y))
            {
                changeStep(menu);
            }
            else if(collisionWithMouse(choixStart.rect,event.button.x,event.button.y))
            {
	      if(modeStep == READY) // si le joueur a bien choisi une salle
                changeStep(game);
            }
            else if(collisionWithMouse(choixConnect.rect,event.button.x,event.button.y))
            {
                modeStep=CONNECT;
            }
            if(collisionWithMouse(ipAsk.rect,event.button.x,event.button.y) && modeStep == GETIP) // si une nouvelle ip est fournie
	    {
	      ipServer.select = true;
	      choixConnect.select=false;
	      modeStep = GETIP; // on n'affiche plus le choix des salles
	    }
	    else
	      ipServer.select=false;

        }
        else if( event.type == SDL_MOUSEMOTION )
        {
            choixQuit.select=collisionWithMouse(choixQuit.rect,event.motion.x,event.motion.y);
            choixBack.select=collisionWithMouse(choixBack.rect,event.motion.x,event.motion.y);
	    if(modeStep==READY)
	      choixStart.select=collisionWithMouse(choixStart.rect,event.motion.x,event.motion.y);
	    if(modeStep==GETIP)
	      choixConnect.select=collisionWithMouse(choixConnect.rect,event.motion.x,event.motion.y);
        }
        else if ( event.type == SDL_KEYUP )
	{
	  if ( event.key.keysym.sym == SDLK_DELETE || event.key.keysym.sym == SDLK_BACKSPACE )
            {
                if(ipServer.select && strlen(ipText)!=0)
		{
		  ipText[strlen(ipText)-1]='\0';
		  updatePickableText(&ipServer,ipText,150,100,8);
		}
                printf("eventLogin: character erased\n");
            }
	}
        switch(event.type)
        {
        case SDL_QUIT:
            changeStep(end);
            break;
	case SDL_TEXTINPUT:
	  if(ipServer.select)
	  {
            if(strlen(ipText)<100-1)
            {
                strcat(ipText, event.text.text);
            }
            updatePickableText(&ipServer,ipText,150,100,8);
            printf("eventMode: ipText = %s\n",ipText);
	  }
            break;
        }
    }
}

static int renderinitialised = 0;

void initModeRender()
{
    strcpy(ipText,"127.0.0.1");
    Background = createPicture(BACKGROUNDPATH,0,0,1);
    
    choixQuit = createPickableText("Exit",400,550,8);
    choixBack = createPickableText("Return",100,550,8);
    choixStart = createPickableText("Start game",100,450,8);
    
    ipAsk = createText("Server IP",20,100,8,false);
    ipServer = createPickableText(ipText,150,100,8);
    choixConnect = createPickableText("Connect",400,100,8);
    
    connecting = createText("Connecting to server ...",150,300,6,false);
    
    renderinitialised=1;
    modeStep=GETIP;
}
void renderMode()
{
    if(renderinitialised==0)
        return;
    renderImage(Background);
    
    renderImage(ipAsk);
    if(modeStep==CONNECT)
      renderImage(connecting);
    renderPickableImage(ipServer);
    renderPickableImage(choixConnect);
    renderPickableImage(choixQuit);
    renderPickableImage(choixBack);
    renderPickableImage(choixStart);
}

void freeModeRender()
{
    if(renderinitialised==0)
    {
        printf("freeModeRender: ne peut pas liberer les ressources car elles n'ont pas etaient inititialisé\n");
        return;
    }
    renderinitialised=0;
    freePickableImage(choixConnect);
    freePickableImage(choixQuit);// Libération de la mémoire associée aux textures
    freePickableImage(ipServer);
    freeImage(ipAsk);
    freeImage(connecting);
    freePickableImage(choixBack);
    freePickableImage(choixStart);
    freeImage(Background);

    printf("freeModeRender: liberation des ressources\n");
}
