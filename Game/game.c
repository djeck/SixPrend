#include "game.h"

static Button choixQuit;
static Button choixBack;

static Picture Background;

static Card table[RANGEE][CPRANGEE]; // chaque carte de la table, 0 dès la fin d'une rangee

static Card poignee[HAND]; // la position de chaque carte da la main pour l'y afficher à l'écran, 0 dès la fin de la main

static Joueur joueurs[MAXJOUEUR]; // des donnees sur tout les joueurs

static Text joueurNom[MAXJOUEUR];
static Text joueurPoint[MAXJOUEUR];

static Text waitInstruction;

static Button playAgain;

static ChatBox chat;

static bool haveToChoose; // mis à jour par le thread de reception si le serveur attend une donnee du client
static bool haveToUpPlayer; // dois mettre à jour les donnes des joueurs
static bool endGame;

void CGameData(Data* data) // callback pour le thread de reception pour tout type de paquet de donnée
{
    if(data->dataType == MSG && strlen(data->tab)>1) // un message (non null) est reçu, on l'ajoute au chat
    {
        sprintf(chat.input.text,"%2d) %s",data->from,data->tab);
        chat.update = true;// sera mis a jour par le thread principale
    }
    else if(data->dataType == GAME && data->car == GAME_CHOICE)
    {
        haveToChoose=true;
    }
    else if(data->dataType == GAME && data->car == END_GAME)
    {
        endGame=true;
    }
    else if(data->dataType == GAME && data->car == GAME_START)
    {
        endGame=false;
    }
    //printData(data);
}
void CGameList(DataList* data) // callback datalist, si le thread de reception a une liste de salle de jeu disponible
{
    printf("CGameList : SHOULDN T APPEND\n");
}
void CGameGame(DataGame* data) // callback datagame, si le thread de reception a une donnee de jeu
{
    printf("CGameGame: DONNES RECU\n");
    int i,z;
    for(i=0; i<RANGEE; i++) // on met à jour la table
        for(z=0; z<CPRANGEE; z++)
            table[i][z].id=data->table[i][z];

    for(i=0; i<MAXJOUEUR; i++)
    {
        strcpy(joueurs[i].nom,data->users[i]);
        joueurs[i].tete=data->scores[i];
    }
    for(i=0; i<HAND; i++)
        poignee[i].id=data->hand[i];
    haveToUpPlayer=true;
}

//met à jour les données à afficher grâce au tableau joueurs[]
void updateJoueur()
{
    char buff[100];
    int i;
    for(i=0; i<MAXJOUEUR; i++)
    {
        updateText(&joueurNom[i],joueurs[i].nom); // mis a jour des noms des joueurs
        sprintf(buff,"%d",joueurs[i].tete);
        updateText(&joueurPoint[i],buff); // mis à jour des points
    }
    haveToUpPlayer=false; // done
}

//crée les données à afficher grâce au tableau joueurs[]
void createJoueur()
{
    int i;
    for(i=0; i<MAXJOUEUR; i++)
    {
        joueurNom[i] =  createText("",POSJOUEUR_X-100,POSJOUEUR_Y + i*(SIZEJOUEUR),10); // mis a jour des noms des joueurs
        joueurPoint[i] =  createText("",POSJOUEUR_X-80,POSJOUEUR_Y + i*(SIZEJOUEUR) + 17,10);  // mis à jour des points
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

void CCard(int id)
{
    haveToChoose=false;
    choice(id);
}
void eventGame()
{
    SDL_Event event;
    int i;

    while (SDL_PollEvent(&event))
    {
        inputChatBox(&chat,&event);
        inputButton(&choixQuit,&event);
        if(endGame)
            inputButton(&playAgain,&event);
        inputButton(&choixBack,&event);
        if(haveToChoose)
            for(i=0; i<HAND && poignee[i].id>0 && poignee[i].id<=104; i++) // on calcule les positons aux quelles on affichera chaque cartes de la main
                eventCard(&event,&poignee[i],&CCard);
        switch(event.type)
        {
        case SDL_QUIT:
            sendQuit();
            changeStep(end);
            break;
        }
    }
}

void CGameMsg(char* msg) // on valide un message dans le chat (entrer)
{
    sendMsg(msg);
}

void CQuitGame() // quit game callback
{
    sendQuit();
    changeStep(end);

}
void CGameMenu()
{
    sendQuit();
    changeStep(menu);

}
void CRestart()
{
    startGame();
}
static int renderinitialised = 0;


void initGameRender()
{

    Background = createPicture(BACKGROUNDPATH,0,0,1);

    updateCallback(&CGameData,&CGameList,&CGameGame);

    choixQuit = createButton("Exit",400,520,8);
    choixBack = createButton("Return",100,500,8);
    waitInstruction =createText("waiting for other player",300,300,8);
    playAgain = createButton("Play again",300,350,6);

    chat = createChatBox(500,350);

    haveToChoose = true;
    haveToUpPlayer = false;
    endGame=false;

    initCard();

    chat.callback = &CGameMsg;
    choixQuit.callback = &CQuitGame;
    choixBack.callback = &CGameMenu;
    playAgain.callback = &CRestart;

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
        strcpy(joueurs[i].nom,"");
        joueurs[i].tete=0;
        joueurs[i].rect.x = POSJOUEUR_X;
        joueurs[i].rect.y = POSJOUEUR_Y + i*(SIZEJOUEUR);
    }
    //ordonner(); pour ranger les cartes

    createJoueur();
    renderinitialised=1;
    setWait(false); // le thread de reception peut metre à jour les donnees
}
void renderGame()
{
    int i,z;
    if(renderinitialised==0)
        return;
    if(haveToUpPlayer)
        updateJoueur();
    renderPicture(&Background);
    for(i=0; i<HAND && poignee[i].id>0 && poignee[i].id<=104; i++) // pour toutes les cartes de la main tant que l'on en a pas d'invalide
        renderCard(&poignee[i]);
    for(i=0; i<RANGEE; i++)
        for(z=0; z<CPRANGEE && table[i][z].id>0 && table[i][z].id<=104; z++)
            renderCard(&table[i][z]);

    for(i=0; i<MAXJOUEUR; i++)
    {
        renderText(&joueurNom[i]);
        if(joueurs[i].tete > 0)
            renderText(&joueurPoint[i]);
    }
    if(!haveToChoose && !endGame)
        renderText(&waitInstruction);
    if(endGame)
        renderButton(&playAgain);
    renderChatBox(&chat);
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
    freeButton(&playAgain);
    freeText(&waitInstruction);
    freeButton(&choixQuit);
    freeRessourcesReseau();
    freeChatBox(&chat);
    freeButton(&choixBack);
    freePicture(&Background); // Libération de la mémoire associée à la texture

    printf("freeGameGame: liberation des ressources\n");
}
