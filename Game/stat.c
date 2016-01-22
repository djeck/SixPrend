#include "stat.h"
#define FILESTATS "./media/stats.dat"

static PickableImage choixBack;
static Image Background;

void eventStat()
{
  SDL_Event event;
	while (SDL_PollEvent(&event))
	{
	  if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT )
	  {
	    if(collisionWithMouse(choixBack.rect,event.button.x,event.button.y))
	    {
	      changeStep(menu);
	    }
	      
	  }
	  else if( event.type == SDL_MOUSEMOTION )
	  {
	      choixBack.select=collisionWithMouse(choixBack.rect,event.motion.x,event.motion.y);
	  }
		switch(event.type)
		{
			case SDL_QUIT:
				changeStep(end);
			break;
		}
	}
}

static int renderinitialised = 0;

void initStatRender()
{
	
	Background = createPicture(BACKGROUNDPATH,0,0,1);
	
	choixBack = createPickableText("Return",100,500,8);
	
	renderinitialised=1;
}
void renderStat()
{
	if(renderinitialised==0)
		return;
	renderImage(Background);
	renderPickableImage(choixBack);
}

void freeStatRender()
{
	if(renderinitialised==0)
	{
	  printf("freeStatRender: ne peut pas liberer les ressources car elles n'ont pas etaient inititialisé\n");
		return;
	}
	renderinitialised=0;
	freePickableImage(choixBack);
	freeImage(Background); // Libération de la mémoire associée à la texture

	printf("freeStatRender: liberation des ressources\n");
}

void loadStatFromFile()
{
    FILE *fic;
    int i=0;
    fic=fopen(FILESTATS,"r");
    if(fic==NULL)
    {
        printf("loadStatFromFile: l'ouverture n'est pas bonne\n");
    }
    else
    {
        while(!feof(fic) && fread(&stats[i],sizeof(Statistique),1,fic))
        {
            i++;
        }
        fclose(fic);
    }
    tailleStats = i;
}

void ajout_stat(bool victoire)
{
    FILE *fic;
    int i;
    bool trouve =false;

    loadStatFromFile();
    for(i=0; i<tailleStats && !trouve; i++)
    {
        if(strcmp(utilisateur,stats[i])==0) // trouve
        {
            if(victoire==true)
            {
                stats[i].nb_vic=stats[i].nb_vic+1;
            }
            else
            {
                stats[i].nb_def=stats[i].nb_def+1;
            }
            trouve=true;
        }

    }
    if(!trouve)
    {
        if(tailleStats < MAXSTAT)
        {
          strcpy(utilisateur,stats[tailleStats].nom);
          stats[tailleStats].nb_vic=0;
          stats[tailleStats].nb_def=0;
          tailleStats++;
        }
        else
        {
            printf("ajout_stat: taille max atteint\n");
        }
    }
    fic=fopen(FILESTATS,"w");
    if(fic==NULL)
    {
        printf("ajout_stat: l'ouverture n'est pas bonne\n");
    }
    else
    {
        for(i=0;i<tailleStats;i++)
        {
            fwrite(&stats[i],sizeof(Statistique),1,fic);
        }
        fclose(fic);
    }
}
