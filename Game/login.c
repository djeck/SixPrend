#include "login.h"

extern int terminer;
static char text[200];

void eventLogin()
{
	SDL_Event event;
    int havetoup=0;
	while (SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_QUIT:
				printf("eventLogin: event quit received\n");
				terminer = 1;
			break;
			case SDL_KEYUP:
				if ( event.key.keysym.sym == SDLK_DELETE || event.key.keysym.sym == SDLK_BACKSPACE )
				{
					text[strlen(text)-1]='\0';
					printf("eventLogin: character erased\n");
					havetoup=1;
				}
				break;
			case SDL_TEXTINPUT:
				if(strlen(text)<199)
					strcat(text, event.text.text);
				printf("eventLogin: buffer = %s\n",text);
				havetoup=1;
                  break;

		}
	}
	if(havetoup==1)
        updateText(text);
}

extern SDL_Renderer* renderer;
static int renderinitialised = 0;

static SDL_Texture* tBackground;
static SDL_Surface* sBackground;
static SDL_Rect rBackground= { 0,0, 800, 600};

static SDL_Texture* ttext;
static SDL_Surface *stext;
static SDL_Color color = {0,0,0};
static TTF_Font* font;
static SDL_Rect rtext= { 100,200, 300, 50};

void initLoginRender()
{

	/*****************  Image de fond   ***********************/

	sBackground = SDL_LoadBMP(BACKGROUNDPATH);
	if ( !sBackground )
	{
		printf("initLoginRender: impossible de creer le sprite de l'image de fond, impossible d'ouvrir le fichier\n");
		terminer=1;
		return;
	}
	tBackground = SDL_CreateTextureFromSurface(renderer,sBackground); // Préparation du sprite
	if (! tBackground )
	{
		printf("initLoginRender: impossible de cree la texture de l'image de fond\n");
		terminer=1;
		return;
	}

	/*****************  TEXT   ***********************/

	font = TTF_OpenFont(FONTPATH, FONTSIZE);
	if (font == NULL)
	{
		printf("initLoginRender: impossible de d'ouvrir le fichier de font\n");
		terminer=1;
		return;
	}

	updateText("enter your username");

	renderinitialised=1;
}

void updateText(char str[])
{


    stext = TTF_RenderText_Solid(font,str,color);
	if (! stext )
	{
		printf("initLoginRender: impossible de cree la surface du text\n");
		terminer=1;
		return;
	}

	ttext = SDL_CreateTextureFromSurface(renderer,stext);
	if (! ttext )
	{
		printf("initLoginRender: impossible de cree la texture du text\n");
		terminer=1;
		return;
	}

	rtext.h = stext->h/5;
    rtext.w= stext->w/5;
}

void renderLogin()
{
	if(renderinitialised==0)
		return;
	SDL_RenderCopy(renderer,tBackground,NULL,&rBackground); // Copie du sprite grâce au SDL_Renderer
	SDL_RenderCopy(renderer,ttext,NULL,&rtext);
}

void freeLoginRender()
{
	if(renderinitialised==0)
	{
	  printf("freeLoginRender: ne peut pas liberer les ressources car elles n'ont pas etaient inititialisé\n");
		return;
	}

    renderinitialised=0; // pour etre sur que on ne dessine pas avec les ressources qui ne sont plus disponiblent
    SDL_DestroyTexture(ttext);
	SDL_FreeSurface(stext);
	TTF_CloseFont(font);
	SDL_DestroyTexture(tBackground); // Libération de la mémoire associée à la texture
	SDL_FreeSurface(sBackground);
	printf("freeLoginRender: liberation des ressources\n");
}
