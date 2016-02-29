#include "mode.h"

static PickableImage choixQuit;
static PickableImage choixStart;
static PickableImage choixBack;
static Image Background;

static Image ipAsk;
static PickableImage ipServer;

static char ipText[100];

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
                changeStep(game);
            }
            ipServer.select = collisionWithMouse(ipAsk.rect,event.button.x,event.button.y);

        }
        else if( event.type == SDL_MOUSEMOTION )
        {
            choixQuit.select=collisionWithMouse(choixQuit.rect,event.motion.x,event.motion.y);
            choixBack.select=collisionWithMouse(choixBack.rect,event.motion.x,event.motion.y);
            choixStart.select=collisionWithMouse(choixStart.rect,event.motion.x,event.motion.y);
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
    
    choixQuit = createPickableText("Exit",400,500,8);
    choixBack = createPickableText("Return",100,450,8);
    choixStart = createPickableText("Start game",150,200,6);
    
    ipAsk = createText("Server IP",20,100,8,false);
    ipServer = createPickableText(ipText,150,100,8);

    renderinitialised=1;
}
void renderMode()
{
    if(renderinitialised==0)
        return;
    renderImage(Background);
    
    renderImage(ipAsk);
    renderPickableImage(ipServer);
    
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
    freePickableImage(choixQuit);// Libération de la mémoire associée aux textures
    freePickableImage(ipServer);
    freeImage(ipAsk);
    freePickableImage(choixBack);
    freePickableImage(choixStart);
    freeImage(Background);

    printf("freeModeRender: liberation des ressources\n");
}
