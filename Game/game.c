#include "game.h"

static PickableImage choixQuit;
static PickableImage choixBack;
static Image Background;

static Image ok; // image pour les joueurs connecté
static Image no; // image pour les joueur non connecté
static Image robot; // image pour les robots

static Image card[NB_CARD]; // card[0] contient la carte 1 ...

static int table[RANGEE][CPRANGEE]; // chaque carte de la table, 0 dès la fin d'une rangee
static SDL_Rect posTable[RANGEE][CPRANGEE]; // la position de chaque carte posee sur la table

static int poignee[HAND]; // la main de l'utilisateur, contient le numero de la carte à afficher [1,104]
static SDL_Rect posPoignee[HAND]; // la position de chaque carte da la main pour l'y afficher à l'écran, 0 dès la fin de la main

static int nombreJoueur; // nombre de joueur au total
static Joueur joueurs[MAXJOUEUR]; // des donnees sur tout les joueurs

static Image joueurNom[MAXJOUEUR];
static Image joueurPoint[MAXJOUEUR];

void updateJoueur()
{
    char buff[10];
    int i;
    for(i=0; i<MAXJOUEUR; i++)
    {
        joueurNom[i] =  createText(joueurs[i].nom,POSJOUEUR_X-100,POSJOUEUR_Y + i*(SIZEJOUEUR),10,false); // mis a jour des noms des joueurs
        sprintf(buff,"%d",joueurs[i].tete);
        joueurPoint[i] =  createText(buff,POSJOUEUR_X-80,POSJOUEUR_Y + i*(SIZEJOUEUR) + 17 ,10,false); // mis à jour des points
    }
}

void ordonner()
{
    // ranger les cartes par ordre croissant
    int i,buff;
    for(i=0; i<HAND && poignee[i]> 0 && poignee[i]<104; i++)
    {
        if(i+1<HAND && poignee[i+1]> 0 && poignee[i+1]<=104 && poignee[i] > poignee[i+1]) // on est pas à la derniere carte de la main et la carte qui suit est plus grande
        {
            buff= poignee[i];
            poignee[i] = poignee[i+1];
            poignee[i+1]=buff;
        }
    }

}

void eventGame()
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

        }
        else if( event.type == SDL_MOUSEMOTION )
        {
            choixQuit.select=collisionWithMouse(choixQuit.rect,event.motion.x,event.motion.y);
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

void initGameRender()
{
    printf("initGameRender: début\n");

    nombreJoueur=2;

    Background = createPicture(BACKGROUNDPATH,0,0,1);

    ok = createPicture(OKPATH,0,0,1);
    no = createPicture(NOPATH,0,0,1);
    robot = createPicture(ROBOTPATH,0,0,1);

    choixQuit = createPickableText("Exit",400,520,8);
    choixBack = createPickableText("Return",100,500,8);

    int i,z;
    char path[10];
    char buff[10];

    for(i=0; i<NB_CARD; i++) // chargement des ressources pour afficher toutes les cartes
    {
        sprintf(path,"./media/%d.bmp",i+1);
        printf("initGameRender: chagement de la carte %s\n",path);
        card[i] = createPicture(path,0,0,1);
    }

    for(i=0; i<HAND; i++) // on s'assure que la main est bien vide
        poignee[i]=0;

    for(i=0; i<RANGEE; i++) // on s'assure qu'il n'y ait pas de cartes sur la table
        for(z=0; z<CPRANGEE; z++)
            table[i][z]=0;

    for(i=0; i<HAND; i++) // on calcule les positons aux quelles on affichera chaque cartes de la main
    {
        posPoignee[i].x = POSHAND_X + i*(card[0].rect.w + DECHAND);
        posPoignee[i].y = POSHAND_Y;
        posPoignee[i].w = card[0].rect.w;
        posPoignee[i].h = card[0].rect.h;
    }

    for(i=0; i<RANGEE; i++) // on calcule les positions des cartes de la tables
        for(z=0; z<CPRANGEE; z++)
        {
            /*
             * i : rangee [0;3]
             * z : carte [0;5]
             */
            posTable[i][z].x = POSTABLE_X + z*(card[0].rect.w + DECHAND); // l'ecart entre les cartes est le même que pour la main
            posTable[i][z].y = POSTABLE_Y + i*(card[0].rect.h + DECRANGEE);
            posTable[i][z].w = card[0].rect.w;
            posTable[i][z].h = card[0].rect.h;
        }

    for(i=0; i<MAXJOUEUR; i++)
    {
        strcpy(joueurs[i].nom,"unused");
        joueurs[i].tete=0;
        joueurs[i].rect.x = POSJOUEUR_X;
        joueurs[i].rect.y = POSJOUEUR_Y + i*(SIZEJOUEUR);
        joueurs[i].rect.w = ok.rect.w;
        joueurs[i].rect.h = ok.rect.h;
        joueurNom[i] =  createText(joueurs[i].nom,POSJOUEUR_X-100,POSJOUEUR_Y + i*(SIZEJOUEUR),10,false);
        sprintf(buff,"%d",joueurs[i].tete);
        joueurPoint[i] =  createText(buff,POSJOUEUR_X-80,POSJOUEUR_Y + i*(SIZEJOUEUR) + 17 ,10,false);
    }

    //pour test
    nombreJoueur=10;
    strcpy(joueurs[5].nom,"djeck");
    joueurs[0].type=BOT;
    joueurs[2].type=OK;
    poignee[0] = 17;
    poignee[1] = 2;
    poignee[2] = 16;
    poignee[3] = 84;
    poignee[4] = 0;
    poignee[5] = 32;
    table[0][0]=86;
    table[0][1]=4;
    table[1][0]=65;
    table[2][0]=45;
    table[3][0]=34;
    ordonner();
    updateJoueur();

    renderinitialised=1;
}
void renderGame()
{
    int i,z;
    if(renderinitialised==0)
        return;
    renderImage(Background);
    for(i=0; i<HAND && poignee[i]>0 && poignee[i]<=104; i++) // pour toutes les cartes de la main tant que l'on en a pas d'invalide
        renderIn(card[poignee[i]-1],posPoignee[i]);
    for(i=0; i<RANGEE; i++)
        for(z=0; z<CPRANGEE && table[i][z]>0 && table[i][z]<=104; z++)
            renderIn(card[table[i][z]-1],posTable[i][z]);

    for(i=0; i<nombreJoueur; i++)
    {
        if(joueurs[i].type == OK)
            renderIn(ok,joueurs[i].rect);
        else if(joueurs[i].type == BOT)
            renderIn(robot,joueurs[i].rect);
        else
            renderIn(no,joueurs[i].rect);
        renderImage(joueurNom[i]);
        renderImage(joueurPoint[i]);
    }

    renderPickableImage(choixQuit);
    renderPickableImage(choixBack);
}

void freeGameRender()
{
    if(renderinitialised==0)
    {
        printf("freeGameGame: ne peut pas liberer les ressources car elles n'ont pas etaient inititialisé\n");
        return;
    }
    renderinitialised=0;
    int i;
    for(i=0; i<NB_CARD; i++)
    {
        freeImage(card[i]);
    }
    for(i=0; i<MAXJOUEUR; i++)
    {
        freeImage(joueurNom[i]);
        freeImage(joueurPoint[i]);
    }
    freePickableImage(choixQuit);
    freePickableImage(choixBack);
    freeImage(ok);
    freeImage(no);
    freeImage(robot);
    freeImage(Background); // Libération de la mémoire associée à la texture

    printf("freeGameGame: liberation des ressources\n");
}
