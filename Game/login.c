#include "login.h"

static char username[SIZESTR];
static char password[SIZESTR];

static Image imgtext;

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
				changeStep(end);
			break;
			case SDL_KEYUP:
				if ( event.key.keysym.sym == SDLK_DELETE || event.key.keysym.sym == SDLK_BACKSPACE )
				{
					text[strlen(text)-1]='\0';
					printf("eventLogin: character erased\n");
					havetoup=1;
				}
				else if( event.key.keysym.scancode == SDL_SCANCODE_RETURN)
				{
					printf("eventLogin: input confirmed\n");
					if(step==rLog) // si l'utilisateur à validé la saisie du nom d'utilisateur
					{
					  strcpy(username,text); // on garde le nom d'utilisateur de côté
					  imgtext = getText("Enter your password",100,200,5);
					  text[0]='\0';
					  step = rPass; // on lui demande le mot de passe
					}
					else if(step==rPass)// sinon si l'utilisateur valide le mot de passe saisie
					{
					  strcpy(password,text);
 					  int resultat = identifier();
					   switch(resultat)
					   {
					     case 0: // mot de passe faux
					       printf("eventLogin: bad password\n");
					       imgtext = getText("Try again...",100,200,5);
					       text[0]='\0';//on efface tout
					       step=rLog; // il doit tout ressaisir
					       break;
					     case 1: // bien identifier
					       printf("eventLogin: successfully identified\n");
					       strcpy(utilisateur,username);
					       changeStep(menu);
					       break;
					     case 2: // nouveau compte
					       printf("eventLogin: new user registred\n");
					       strcpy(utilisateur,username);
					       changeStep(menu);
					       break;
					     default:
					      printf("eventLogin: error, identifer(char*,char*) shouldnt return %d\n",resultat);
					      imgtext = getText("Error  try again...",100,200,5);
					      text[0]='\0';//on efface tout
					      step=rLog; // il doit tout ressaisir
					   }
					}
				}
				break;
			case SDL_TEXTINPUT:
				if(strlen(text)<SIZESTR-1)
					strcat(text, event.text.text);
				printf("eventLogin: buffer = %s\n",text);
				havetoup=1;
                  break;

		}
	}
	if(havetoup==1)
        imgtext = getText(text,100,200,5);;
}

extern SDL_Renderer* renderer;
static int renderinitialised = 0;

static Image Background;


void initLoginRender()
{
  printf("initLoginRender: debut\n");
	
	Background = getPicture(BACKGROUNDPATH,0,0,1);
	
	imgtext = getText("Enter your username",100,200,5);
	
	step=rLog; // on va commencer par lui demander le nom d'utilisateur
	renderinitialised=1;
}


void renderLogin()
{
	if(renderinitialised==0)
		return;
	renderImage(Background);
	renderImage(imgtext);
}

void freeLoginRender()
{
	if(renderinitialised==0)
	{
	  printf("freeLoginRender: ne peut pas liberer les ressources car elles n'ont pas etaient inititialisé\n");
		return;
	}

    renderinitialised=0; // pour etre sur que on ne dessine pas avec les ressources qui ne sont plus disponiblent
    freeImage(imgtext);
    freeImage(Background);

	printf("freeLoginRender: liberation des ressources\n");
}

int identifier()
{
    FILE *fic;
    char loginlu[SIZESTR],passlu[SIZESTR];
    fic=fopen(FILELOGIN,"r+");
    if(fic==NULL)
    {
        printf("l'ouverture n'est pas bonne\n");
    }
    else
    {
        while(fscanf(fic,"%s %s",loginlu,passlu)==2) // tant qu'il y a des donnes valides à lire
	{
	  if(strcmp(loginlu,username)==0) // le compte existe
	  {
	    if(strcmp(passlu,password)==0) // le mot de passe rentre est valide
	    {
	      fclose(fic);
	      return 1;
	    }
	    else // mot de passe non valide
	    {
	      fclose(fic);
	      return 0;
	    }
	  }
	}
 	//fichier parcouru sans avoir pu trouver le compte: on le cree
	fprintf(fic,"%s %s\n",username,password);
	fclose(fic);
	return 2;
    }
}
