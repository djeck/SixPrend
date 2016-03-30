/**
 * \file stat.c
 * \brief implémentation de l'affichage et gestions des statistiques
 * \author Aubin Detrez et Zongwei WU
 *
 */
#include "stat.h"

static Button choixBack;
static Picture Background;
static Text name; // ligne des noms
static Text vic; // ligne des victoires
static Text def; // ligne des défaites
static Text testname[10]; // chaque nom de joueur
static Text testvic[10]; // les victoires de chaque joueur
static Text testdef[10]; // les défaites de chaque joueur

/*
 * la variable de structure Statistique
 * usage limité au fichier
 */
static Statistique stats[MAXSTAT];
/*
 * le taille du tableau
 */
static int tailleStats;

void eventStat()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        inputButton(&choixBack,&event);

        switch(event.type)
        {
        case SDL_QUIT:
            changeStep(end);
            break;
        }
    }
}

static int renderinitialised = 0;

/**
 * \fn void CStatMenu()
 * \brief callback pour se diriger vers le menu
 * appelé par le bouton par le bouton lors d'un clic
 */
void CStatMenu()
{
    changeStep(menu);
}
void initStatRender()
{

    loadStatFromFile();
    int j=0;
    char nom[200], vics[200], defs[200];
    Background = createPicture(BACKGROUNDPATH,0,0,1);

    choixBack = createButton("Return",100,500,8);


    choixBack.callback = &CStatMenu;

    do
    {
        strcpy(nom,stats[j].nom);
        sprintf(vics,"%d",stats[j].nb_vic);
        sprintf(defs,"%d",stats[j].nb_def);
        j++;
        testname[j-1]=createText(nom,70+j*80,150,9);
        testvic[j-1]=createText(vics,70+j*80,210,9);
        testdef[j-1]=createText(defs,70+j*80,270,9);
    }
    while(j<tailleStats && tailleStats<MAXSTAT);

    loadStatFromFile();
    name = createText("Name:",50,150,10);
    vic = createText("Victoire:",50,210,10);
    def = createText("Default:",50,270,10);

    printf("initStatRender : initialised\n");


    renderinitialised=1;
}
void renderStat()
{
    int j=0;
    if(renderinitialised==0)
        return;

    renderPicture(&Background);

    renderText(&name);
    renderText(&vic);
    renderText(&def);
    do
    {
        renderText(&testname[j]);
        renderText(&testvic[j]);
        renderText(&testdef[j]);
        j++;
    }
    while(j<10);


    renderButton(&choixBack);
}

void freeStatRender()
{
    int j=0;
    if(renderinitialised==0)
    {
        printf("freeStatRender: ne peut pas liberer les ressources car elles n'ont pas etaient inititialisé\n");
        return;
    }
    renderinitialised=0;
    freeText(&name);
    freeText(&vic);
    freeText(&def);
    do
    {
        freeText(&testname[j]);
        freeText(&testvic[j]);
        freeText(&testdef[j]);
        j++;
    }
    while(j<10);
    freeButton(&choixBack);
    freePicture(&Background); // Libération de la mémoire associée à la texture

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
        while(i<MAXSTAT && !feof(fic) && fread(&stats[i],sizeof(Statistique),1,fic))
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
        if(strcmp(getUsername(),stats[i].nom)==0) // trouve
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
    if(!trouve) // le joueur n'a pas encore de statistique
    {
        if(tailleStats < MAXSTAT-1)
        {
            strcpy(stats[tailleStats].nom,getUsername());
            if(victoire==true)
            {
                stats[tailleStats].nb_vic=1;
                stats[tailleStats].nb_def=0;
            }
            else
            {
                stats[tailleStats].nb_def=1;
                stats[tailleStats].nb_vic=0;
            }
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
        for(i=0; i<tailleStats; i++)
        {
            fwrite(&stats[i],sizeof(Statistique),1,fic);
        }
        fclose(fic);
    }
}
