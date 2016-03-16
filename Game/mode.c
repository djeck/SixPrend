#include "mode.h"

static Button choixQuit;
static Button choixStart;
static Button choixBack;
static Picture Background;
static Button choixConnect;

static Text ipAsk;
static TextBox ipServer;

static Text connecting; //message de connection
static Button choixList;

static Text textCreate;
static Button choixCreate;
static TextBox salleName;

static MultiText list;

static ChatBox chat;




/*
 * GETIP le joueur saisie de l'ip du serveur, premiere étape et on y retourne quant on change l'ip du serveur
 * CONNECT connection en cour au serveur
 * SALLE le joueur choisi la salle à rejoindre ou à créer
 * READY tout choix ok, reste au client à cliquer sur game
 */
enum {GETIP=0, CONNECT=1, SALLE=2,READY=3,GO=4} modeStep;

void eventMode()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        inputTextBox(&ipServer,&event);
        inputButton(&choixQuit,&event);
        inputButton(&choixBack,&event);
        if(modeStep == SALLE)
        {
            inputMultiText(&list,&event);
            inputChatBox(&chat,&event);
            inputTextBox(&salleName,&event);
            inputButton(&choixCreate,&event);
            inputButton(&choixList,&event);
        }
        else if(modeStep==READY)
        {
            inputButton(&choixStart,&event);
            inputChatBox(&chat,&event);
        }

        inputButton(&choixConnect,&event);

        switch(event.type)
        {
        case SDL_QUIT:
            changeStep(end);
            break;
        }
    }
}

static int renderinitialised = 0;

void CData(Data* data) // callback pour le thread de reception pour tout type de paquet de donnée
{
    if(data->dataType == CONN && data->car == CONN_OK) // connection établie avec success
    {
        modeStep = SALLE;
        sprintf(chat.input.text,"! Connection established");
        chat.update = true; // sera mis a jour par le thread principale
        askList();
    }
    else if(data->dataType == MSG && strlen(data->tab)>1) // un message (non null) est reçu, on l'ajoute au chat
    {
        printf("Message recu: <<%s>>\n",data->tab);
        sprintf(chat.input.text,"%2d) %s",data->from,data->tab);
        chat.update = true;// sera mis a jour par le thread principale
    }
    else if(data->dataType == GAME && data->car == GAME_OK)
    {
        modeStep = READY;
    }
    else if(data->dataType == GAME && data->car == GAME_START)
    {
        printf("GAME_start recu, le thread principale va charger la page de jeu\n");
        identifySrv(getUsername());
        modeStep = GO;
        setWait(true);
    }
    else
        printData(data);
}
void CDtList(DataList* data) // callback datalist, si le thread de reception a une liste de salle de jeu disponible
{
    printf("CList\n");
    int compteur=0; // compte le nombre de ligne
    int indice=0; // indice dans data->tab
    int coresp=0;//indice correspondant dans list.text[compteur]
    while(data->tab[indice]!='\0')//tant que l'on est pas à la fin de la chaine
    {
        if(data->tab[indice]=='\n')
        {
            list.text[compteur][coresp]='\0';
            compteur++;
            coresp=0;
        }
        else if(coresp<100 && compteur < NB_LINE)
        {
            list.text[compteur][coresp]=data->tab[indice];
            coresp++;
        }
            indice ++;
    }
    list.update=true;
    list.initialised=true;
}
void CDtGame(DataGame* data) // callback datagame, si le thread de reception a une donnee de jeu
{
    printf("CGame: SHOULDN'T APPEND\n");
}
void CQuit() // on demande à quitter
{
    changeStep(end);
}

void CMenu() // on clic sur le bouton retour menu
{
    changeStep(menu);
}

void CGame() // on demande à commancer le jeu
{
    startGame();
}
void CUpList() // on demande à metre à jour les listes
{
    askList();
}
void CConnect() // on clic sur le bouton connect
{
    modeStep=CONNECT;
    printf("CConnect\n");
    initialisationReseau(ipServer.text,&CData,&CDtList,&CDtGame);
    reception();
    printf("CConnect: done\n");
    list.initialised=false; // par default la liste contient un message non valide comme nom de salle
}
void CMsg(char* msg) // on valide un message dans le chat (entrer)
{
    sendMsg(msg);
}
void CList(char* choix) // on clic sur une salle de la liste des salles
{
    printf("CList : choix = \"%s\"\n",choix);
    join(choix,-1);
}
void CCreate() // l'utilisateur demande à creer la salle
{
    if(strlen(salleName.text)>0)
    {
        printf("CCreate: creation de la salle \"%s\"\n",salleName.text);
        create(salleName.text,-1);
    }
}
void initModeRender()
{
    char ipText[100];
    strcpy(ipText,"127.0.0.1");
    Background = createPicture(BACKGROUNDPATH,0,0,1);

    choixQuit = createButton("Exit",400,550,8);
    choixBack = createButton("Return",100,550,8);
    choixStart = createButton("Start game",100,450,8);

    ipAsk = createText("Server IP",20,100,8);
    ipServer = createTextBox(ipText,150,100,15,30,15,true);
    choixConnect = createButton("Connect",450,100,8);
    chat = createChatBox(500,350);

    connecting = createText("Connecting to server ...",100,300,8);
    list = createMultiText(50,150);
    strcpy(list.text[0],"No available room");
    list.update=true;

    textCreate = createText("create:",400,200,8);
    salleName = createTextBox("",500,200,15,30,8,8);
    choixCreate = createButton("valid",650,200,9);
    choixList = createButton("ask for list",550,240,11);

    choixList.callback = &CUpList;
    choixCreate.callback = &CCreate;
    choixConnect.callback = &CConnect;
    chat.callback = &CMsg;
    choixQuit.callback = &CQuit;
    choixBack.callback = &CMenu;
    choixStart.callback = &CGame;
    list.callback = &CList;

    renderinitialised=1;
    modeStep=GETIP;
}
void renderMode()
{
    if(renderinitialised==0)
        return;

    if(modeStep == GO)
        changeStep(game); // synchronisation de tout les clients, depuis les données du serveur

    renderPicture(&Background);

    renderText(&ipAsk);
    if(modeStep == CONNECT)
        renderText(&connecting);
    renderTextBox(&ipServer);
    renderButton(&choixConnect);
    renderButton(&choixQuit);
    renderButton(&choixBack);
    if(modeStep == READY)
    {
        renderButton(&choixStart);
        renderChatBox(&chat);
    }
    else if(modeStep==SALLE)
    {
        renderChatBox(&chat);
        renderMultiText(&list);
        renderText(&textCreate);
        renderTextBox(&salleName);
        renderButton(&choixCreate);
        renderButton(&choixList);
    }
}

void freeModeRender()
{
    if(renderinitialised==0)
    {
        printf("freeModeRender: ne peut pas liberer les ressources car elles n'ont pas etaient inititialisé\n");
        return;
    }
    renderinitialised=0;
    if(modeStep!=GO) // si on ne l'utilise pas apres
        freeRessourcesReseau();
    freeButton(&choixList);
    freeText(&textCreate);
    freeTextBox(&salleName);
    freeButton(&choixCreate);
    freeButton(&choixConnect);
    freeButton(&choixQuit);// Libération de la mémoire associée aux textures
    freeTextBox(&ipServer);
    freeText(&ipAsk);
    freeText(&connecting);
    freeButton(&choixBack);
    freeButton(&choixStart);
    freePicture(&Background);
    freeChatBox(&chat);
    freeMultiText(&list);

    printf("freeModeRender: liberation des ressources\n");
}

