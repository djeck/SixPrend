/*
 * Comprend les fonctions communes à tout le jeu
 */
#include "inc.h"

void changeStep(MainStep nextStep)
{
  if(nextStep==globalStep)
    return;
  
  switch(globalStep)
  {
    case login:
      	freeLoginRender(); // liberation des ressources du login
      break;
    case menu:
	freeMenuRender();
      break;
    case mode:
      //freeModeRender();
      break;
    case stat:
      //freeStatRender();
      break;
    case game:
      //freeGameRender();
      break;
  }

  switch(nextStep)
  {
    case login:
      printf("changeStep: test\n");
      initLoginRender();
      break;
    case menu:
      initMenuRender();
      break;
    case mode:
      //initModeRender();
      break;
    case stat:
      //initStatRender();
      break;
    case game:
      //initGameRender();
      break;
  }
  globalStep=nextStep;
  printf("changeStep: changement d'etat effectue avec succes\n");
}



static SDL_Color color = {0,0,0};
static SDL_Color colorsel = {255,0,0};

void setTextColor(int r, int g, int b)
{
  color.r=r;
  color.g=g;
  color.b=b;
}

extern renderer;
Image getText(char str[],int x,int y,int size)
{
  printf("getText: debut\n");
	SDL_Surface *stext;
	Image img;
	img.rect.x = x;
	img.rect.y = y;
	
	if(!font)
	  printf("getText: font non charge\n");
	
	if(strlen(str)==0)
	{
	  printf("getText: chaine vide\n");
	  stext = TTF_RenderText_Solid(font," ",color);
	}
	else
	{
	  stext = TTF_RenderText_Solid(font,str,color);/**/
	}
	if (! stext )
	{
		printf("getText: impossible de cree la surface du text\n");
		printf("getText: taille de la chaine: %d\n",strlen(str));
		changeStep(end);
		return;
	}
	
	img.texture = SDL_CreateTextureFromSurface(renderer,stext);
	if (! img.texture )
	{
		printf("getText: impossible de cree la texture du text\n");
		changeStep(end);
		return;
	}

	img.rect.h = stext->h/size;
	img.rect.w = stext->w/size;
	SDL_FreeSurface(stext);
	return img;
}

PickableImage getPickableText(char str[],int x,int y,int size)
{
	SDL_Surface *stext;
	PickableImage img;
	img.select=false;
	img.rect.x = x;
	img.rect.y = y;
	
	if(!font)
	  printf("getText: font non charge\n");
	
	if(strlen(str)==0)
	{
	  printf("getText: chaine vide\n");
	  stext = TTF_RenderText_Solid(font," ",color);
	}
	else
	{
	  stext = TTF_RenderText_Solid(font,str,color);/**/
	}
	if (! stext )
	{
		printf("getText: impossible de cree la surface du text\n");
		printf("getText: taille de la chaine: %d\n",strlen(str));
		changeStep(end);
		return;
	}
	
	img.texture = SDL_CreateTextureFromSurface(renderer,stext);
	if (! img.texture )
	{
		printf("getText: impossible de cree la texture du text\n");
		changeStep(end);
		return;
	}
	SDL_FreeSurface(stext);
	
	stext = TTF_RenderText_Solid(font,str,colorsel);/**/
	if (! stext )
	{
		printf("getText: impossible de cree la surface du text\n");
		printf("getText: taille de la chaine: %d\n",strlen(str));
		changeStep(end);
		return;
	}
	
	img.textureselelct = SDL_CreateTextureFromSurface(renderer,stext);
	if (! img.textureselelct )
	{
		printf("getText: impossible de cree la texture du text\n");
		changeStep(end);
		return;
	}

	img.rect.h = stext->h/size;
	img.rect.w = stext->w/size;
	SDL_FreeSurface(stext);
	return img;
}


Image getPicture(char* path, int x, int y,int size)
{
  Image img;
  img.rect.x = x;
  img.rect.y =y;

	SDL_Surface* surface = SDL_LoadBMP(path);
	if ( !surface )
	{
		printf("getPicture: impossible de creer le sprite de l'image de fond, impossible d'ouvrir le fichier\n");
		changeStep(end);
		return;
	}
	img.texture = SDL_CreateTextureFromSurface(renderer,surface); // Préparation du sprite
	if (! img.texture )
	{
		printf("getPicture: impossible de cree la texture de l'image de fond\n");
		changeStep(end);
		return img;
	}
	img.rect.h = surface->h/size;
	img.rect.w = surface->w/size;
	SDL_FreeSurface(surface);
	return img;
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
void renderImage(Image img)
{
  SDL_RenderCopy(renderer,img.texture,NULL,&img.rect);
}
void renderPickableImage(PickableImage img)
{
  if(img.select)
   SDL_RenderCopy(renderer,img.textureselelct,NULL,&img.rect);
  else
    SDL_RenderCopy(renderer,img.texture,NULL,&img.rect);
}
void freeImage(Image img)
{
SDL_DestroyTexture(img.texture);
}
void freePickableImage(PickableImage img)
{
SDL_DestroyTexture(img.texture);
SDL_DestroyTexture(img.textureselelct);
}

