#include "mode.h"

static Button choixQuit;
static Button choixStart;
static Button choixBack;
static Picture Background;
static Button choixConnect;
static ChatBox chat;

static Text ipAsk;
static TextBox ipServer;

static Text connecting; //message de connection
static MultiText list;

/*
 * GETIP le joueur saisie de l'ip du serveur, premiere étape et on y retourne quant on change l'ip du serveur
 * CONNECT connection en cour au serveur
 * SALLE le joueur choisi la salle à rejoindre ou à créer
 * READY tout choix ok, reste au client à cliquer sur game
 */
enum {GETIP=0, CONNECT=1, SALLE=2,READY=3} modeStep;

void eventMode()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
	inputTextBox(&ipServer,&event);
	inputButton(&choixQuit,&event);
	inputButton(&choixBack,&event);
	inputChatBox(&chat,&event);
	if(modeStep==READY)
	  inputButton(&choixStart,&event);
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

void CData(Data* data) // confimation de la connection au serveur
{
	if(data->dataType == CONN && data->car == CONN_OK)
	{
	  modeStep = SALLE;
	  sprintf(chat.input.text,"! Connection established");
	  chat.update = true; // sera mis a jour par le thread principale
	  askList();
	}
	else if(data->dataType == MSG && strlen(data->tab)>1)
	{
	  printf("Message recu: <<%s>>\n",data->tab);
	  sprintf(chat.input.text,"%2d) %s",data->from,data->tab);
	  chat.update = true;// sera mis a jour par le thread principale
	}
}
void CDtList(DataList* data) // callback datalist
{
printf("CList\n");
char str[100];
int i=0;
while(sscanf(data->tab,"%s\n",str)==1 && i<NB_LINE)
{
  strcpy(list.text[i],str);
  i++;
  list.update=true;
}
}
void CDtGame(DataGame* data) // callback datagame
{
  printf("CGame\n");
}
    void CQuit()
    {
      changeStep(end);
    }
    
    void CMenu()
    {
      changeStep(menu);
    }
    
    void CGame()
    {
      changeStep(game);
    }
    
    void CConnect()
    {
      modeStep=CONNECT;
      printf("CConnect\n");
      initialisationReseau(ipServer.text,&CData,&CDtList,&CDtGame);
      reception();
      printf("CConnect: done\n");
    }
    void CMsg(char* msg)
    {
      sendMsg(msg);
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
    
    choixConnect.callback = &CConnect;
    chat.callback = &CMsg;
    choixQuit.callback = &CQuit;
    choixBack.callback = &CMenu;
    choixStart.callback = &CGame;
    
    renderinitialised=1;
    modeStep=GETIP;
}
void renderMode()
{
    if(renderinitialised==0)
        return;
    renderPicture(&Background);
    
    renderText(&ipAsk);
    if(modeStep==CONNECT)
      renderText(&connecting);
    renderTextBox(&ipServer);
    renderButton(&choixConnect);
    renderButton(&choixQuit);
    renderButton(&choixBack);
    renderButton(&choixStart);
    if(modeStep==SALLE)
    {
      renderChatBox(&chat);
      renderMultiText(&list);
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
    freeRessourcesReseau();
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

