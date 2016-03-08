#include "game.h"

static Button choixQuit;
static Button choixBack;

static Picture Background;

static Card table[RANGEE][CPRANGEE]; // chaque carte de la table, 0 dès la fin d'une rangee

static Card poignee[HAND]; // la position de chaque carte da la main pour l'y afficher à l'écran, 0 dès la fin de la main

static int nombreJoueur; // nombre de joueur au total < MAXJOUEUR
static Joueur joueurs[MAXJOUEUR]; // des donnees sur tout les joueurs

static Text joueurNom[MAXJOUEUR];
static Text joueurPoint[MAXJOUEUR];

//met à jour les données à afficher grâce au tableau joueurs[]
void updateJoueur()
{
    char buff[10];
    int i;
    for(i=0; i<MAXJOUEUR; i++)
    {
        updateText(&joueurNom[i],joueurs[i].nom); // mis a jour des noms des joueurs
        sprintf(buff,"%d",joueurs[i].tete);
        updateText(&joueurPoint[i],buff); // mis à jour des points
    }
  
}

//crée les données à afficher grâce au tableau joueurs[]
void createJoueur()
{
    char buff[10];
    int i;
    for(i=0; i<MAXJOUEUR; i++)
    {
        joueurNom[i] =  createText(joueurs[i].nom,POSJOUEUR_X-100,POSJOUEUR_Y + i*(SIZEJOUEUR),10); // mis a jour des noms des joueurs
        sprintf(buff,"%d",joueurs[i].tete);
        joueurPoint[i] =  createText(buff,POSJOUEUR_X-80,POSJOUEUR_Y + i*(SIZEJOUEUR) + 17 ,10); // mis à jour des points
    }
}

// range les carte de la main
void ordonner()
{
    // ranger les cartes par ordre croissant
    int i,buff;
    for(i=0; i<HAND && poignee[i].id > 0 && poignee[i].id<104; i++)
    {
        if(i+1<HAND && poignee[i+1].id> 0 && poignee[i+1].id<=104 && poignee[i].id > poignee[i+1].id) // on est pas à la derniere carte de la main et la carte qui suit est plus grande
        {
            buff= poignee[i].id;
            poignee[i].id = poignee[i+1].id;
            poignee[i+1].id=buff;
        }
    }

}

void CCard(int id) {
  printf("CCard: card id %d had been pressed\n",id);
    };
void eventGame()
{
    SDL_Event event;
    int i;
    
    while (SDL_PollEvent(&event))
    {
      inputButton(&choixQuit,&event);
      inputButton(&choixBack,&event);
      for(i=0; i<HAND && poignee[i].id>0 && poignee[i].id<=104; i++) // on calcule les positons aux quelles on affichera chaque cartes de la main
    {
      eventCard(&event,&poignee[i],&CCard);
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
 
    choixQuit = createButton("Exit",400,520,8);
    choixBack = createButton("Return",100,500,8);
    
    initCard();
    
    void CQuitGame() // quit game callback
    {
      changeStep(end);
    };
    void CMenu()
    {
      changeStep(menu);
    };
    choixQuit.callback = &CQuitGame;
    choixBack.callback = &CMenu;

    int i,z;
    for(i=0; i<HAND; i++) // on s'assure que la main est bien vide
        poignee[i].id=0;

    for(i=0; i<RANGEE; i++) // on s'assure qu'il n'y ait pas de cartes sur la table
        for(z=0; z<CPRANGEE; z++)
            table[i][z].id=0;

    for(i=0; i<HAND; i++) // on calcule les positons aux quelles on affichera chaque cartes de la main
    {
        poignee[i].rect.x = POSHAND_X + i*(CARD_W + DECHAND);
        poignee[i].rect.y = POSHAND_Y;
        poignee[i].rect.w = CARD_W;
        poignee[i].rect.h = CARD_H;
	poignee[i].id=0;
	poignee[i].selected=false;
    }

    for(i=0; i<RANGEE; i++) // on calcule les positions des cartes de la tables
        for(z=0; z<CPRANGEE; z++)
        {
            /*
             * i : rangee [0;3]
             * z : cartes de chaque rangée [0;5]
             */
            table[i][z].rect.x = POSTABLE_X + z*(CARD_W + DECHAND); // l'ecart entre les cartes est le même que pour la main
            table[i][z].rect.y = POSTABLE_Y + i*(CARD_H + DECRANGEE);
            table[i][z].rect.w = CARD_W;
            table[i][z].rect.h = CARD_H;
	    table[i][z].id=0;
	    table[i][z].selected=false;
        }

    for(i=0; i<MAXJOUEUR; i++)
    {
        strcpy(joueurs[i].nom,"unused");
        joueurs[i].tete=0;
        joueurs[i].rect.x = POSJOUEUR_X;
        joueurs[i].rect.y = POSJOUEUR_Y + i*(SIZEJOUEUR);
    }

    //pour test
    nombreJoueur=5;
    strcpy(joueurs[0].nom,"mark");
    strcpy(joueurs[1].nom,"polo");
    strcpy(joueurs[2].nom,"patrice");
    strcpy(joueurs[3].nom,"antoine");
    strcpy(joueurs[4].nom,"jack");
    joueurs[0].tete=5;
    
    poignee[0].id = 17;
    poignee[1].id = 2;
    poignee[2].id = 16;
    poignee[3].id = 84;
    poignee[4].id = 0;
    poignee[5].id = 32;
    table[0][0].id=86; 
    table[0][1].id=4;
    table[1][0].id=65;
    table[2][0].id=45;
    table[3][0].id=34;
    ordonner();
    createJoueur();

    renderinitialised=1;
    printf("initGameRender: Fin");
}
void renderGame()
{
    int i,z;
    if(renderinitialised==0)
        return;
    renderPicture(&Background);
    for(i=0; i<HAND && poignee[i].id>0 && poignee[i].id<=104; i++) // pour toutes les cartes de la main tant que l'on en a pas d'invalide
        renderCard(&poignee[i]);
    for(i=0; i<RANGEE; i++)
        for(z=0; z<CPRANGEE && table[i][z].id>0 && table[i][z].id<=104; z++)
            renderCard(&table[i][z]);

    for(i=0; i<nombreJoueur; i++)
    {
        renderText(&joueurNom[i]);
        renderText(&joueurPoint[i]);
    }

    renderButton(&choixQuit);
    renderButton(&choixBack);
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
    detroyCard();
    for(i=0; i<MAXJOUEUR; i++)
    {
        freeText(&joueurNom[i]);
        freeText(&joueurPoint[i]);
    }
    freeButton(&choixQuit);
    freeButton(&choixBack);
    freePicture(&Background); // Libération de la mémoire associée à la texture

    printf("freeGameGame: liberation des ressources\n");
}
