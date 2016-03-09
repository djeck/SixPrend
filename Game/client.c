#include "client.h"

static IPaddress ip;		/* Server address */
static TCPsocket sd;		/* Socket descriptor */
static Data data;
static DataList dataList;
static DataGame dataGame;

static int networkinitialised = 0;
void initialisationReseau(char *strip)
{
  if(isNetInitialised())
  {
    freeRessourcesReseau();
  }
    if (SDLNet_Init() < 0)
    {
        printf("SDLNet_Init: %s\n", SDLNet_GetError());
        return;
    }

    /* Resolve the host we are connecting to */
    if (SDLNet_ResolveHost(&ip, strip, PORT) < 0)
    {
        printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
        return;
    }

    /* Open a connection with the IP provided (listen on the host's port) */
    if (!(sd = SDLNet_TCP_Open(&ip)))
    {
        printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
        return;
    }
    networkinitialised = 1;
}


DataList* receptList()
{
  if(networkinitialised!=1)
    return NULL;
  printf("reception d'une liste\n");
  int receivedByteCount = SDLNet_TCP_Recv(sd, &dataList, sizeof(DataList));
  printf("***************************\n");
  printf("tab: %s\n",dataList.tab);
  printf("end: %d\n",(int)dataList.end);
  printf("received: %d\n",receivedByteCount);
  printf("***************************\n");
  return &dataList;
}

void receptGame()
{
  int i,z;
  if(networkinitialised!=1)
    return;
  
  printf("reception de donnée de jeu\n");
  int receivedByteCount = SDLNet_TCP_Recv(sd, &dataGame, sizeof(DataGame));
  printf("***************************\n");
  printf("received: %d\n",receivedByteCount);
  printf("table: \n");
  for(i=0;i<4;i++)
  {
    for(z=0;z<6;z++)
      printf("%d ",dataGame.table[i][z]);
    printf("\n");
  }
  for(i=0;i<10;i++)
    printf("users %d %s\n",i,dataGame.users[i]);
  for(i=0;i<10;i++)
    printf("turn %d %d\n",i,dataGame.turn[i]);
  for(i=0;i<10;i++)
    printf("scores %d %d\n",i,dataGame.scores[i]);
  for(i=0;i<10;i++)
    printf("hand %d %d\n",i,dataGame.hand[i]);
  printf("***************************\n");
}

static int Treception(void *ptr)
{
    void (*callback)(Data*);
    callback = ptr;
    int cnt = SDLNet_TCP_Recv(sd, &data, sizeof(Data));
  
    printf("received: %d\n",cnt);
    if(data.dataType == CONN)
    {
      printf("données de type CONN reçu\n");
      
        if(data.car == CONN_FULL)
            printf("CONN_FULL Echec de la connection: serveur plein\n");
        else if(data.car == CONN_OK)
            printf("CONN_OK Connection etablie avec success\n");
        else if(data.car == CONN_STOP)
            printf("CONN_STOP le serveur met fin à la connection\n");
        else if(data.car == CONN_ERROR)
            printf("CONN_ERROR erreur inconnue\n");
	else if(data.car == CONN_LIST)
            printf("CONN_LIST ne devrais pas etre envoyé au client\n");
	else if(data.car == CONN_JOIN)
            printf("CONN_JOIN ne devrais pas etre envoyé au client\n");
	else if(data.car == CONN_CREATE)
            printf("CONN_CREATE ne devrais pas etre envoyé au client\n");
	else
	  printf("donnees de nature inconnue\n");
    }
    else if(data.dataType == MSG)
    {
	printf("données de type MSG reçu\n");
    }
    else if(data.dataType == GAME)
    {
      printf("données de type GAMME reçu\n");
      if(data.car == GAME_OK)
            printf("GAME_OK bien connecté à une salle\n");
        else if(data.car == GAME_LOGIN)
            printf("GAME_LOGIN le serveur demande d'envoyer le login\n");
        else if(data.car == GAME_ERROR)
            printf("GAME_ERROR erreur\n");
        else if(data.car == GAME_START)
            printf("GAME_START on peut commencer à jouer\n");
	else if(data.car == GAME_CHOICE)
            printf("GAME_CHOICE le serveur demande aux joueurs de choisir leurs cartes\n");
	else if(data.car == END_TURN)
            printf("END_TURN fin du tour, apprêté vous à recevoir les donnees du jeu\n");
	else if(data.car == END_GAME)
            printf("END_GAME fin du jeu, attend game_start pour recommancer\n");
	else
	  printf("donnees de nature inconnue\n");
    }
    else
      printf("ERROR type de donné inconu\n");
    
    (*callback)(&data);
    return cnt;
}

void reception(void (*callback)(Data*))
{
  
  if(networkinitialised!=1)
    return;
  
  SDL_Thread *thread;
  int threadReturnValue;
  thread = SDL_CreateThread(Treception, "receptData", (void *)callback);
  if (NULL == thread) {
        printf("\nSDL_CreateThread failed: %s\n", SDL_GetError());
    } else {
        SDL_WaitThread(thread, &threadReturnValue);
        printf("\nThread returned value: %d", threadReturnValue);
    }
}

void sendMsg(char *msg)
{
  if(networkinitialised!=1)
    return;
  data.dataType=MSG;
  strcpy(data.tab,msg);
  if (SDLNet_TCP_Send(sd, &data, sizeof(data)) < sizeof(data))
  {
     printf("***********l'envoi a échoué**************\n>");
  }
  printf("envoie éffectué \n");
}
void askList()
{
  if(networkinitialised!=1)
    return;
  data.dataType=CONN;
  data.car=CONN_LIST;
  if (SDLNet_TCP_Send(sd, &data, sizeof(data)) < sizeof(data))
  {
     printf("***********l'envoi a échoué**************\n>");
  }
  printf("envoie éffectué \n");
}
void wait()
{
  printf("press enter to continue\n");
  fflush(stdin);
  getchar();
}
void freeRessourcesReseau()
{
  if(networkinitialised!=1)
  {
    printf("freeRessourcesReseau: ERROR");
    return;
  }
  SDLNet_TCP_Close(sd);
  SDLNet_Quit();
}
void join()
{
  if(networkinitialised!=1)
    return;
  printf("envoie une demande pour rejoindre une salle \n");
  data.dataType=CONN;
  data.car=CONN_JOIN;
  printf("saississez le nom de la salle \n");
  scanf("%s",data.tab);
  printf("saississez le mot de passe -1 sinon \n");
  scanf("%d",&data.from);
  if (SDLNet_TCP_Send(sd, &data, sizeof(data)) < sizeof(data))
  {
     printf("***********l'envoi a échoué**************\n>");
  }
  printf("envoie éffectué \n");
}
void create()
{
  if(networkinitialised!=1)
    return;
  printf("envoie une demande pour creer une salle \n");
  data.dataType=CONN;
  data.car=CONN_CREATE;
  printf("saississez le nom de la salle \n");
  scanf("%s",data.tab);
  printf("saississez le mot de passe -1 sinon \n");
  scanf("%d",&data.from);
  if (SDLNet_TCP_Send(sd, &data, sizeof(data)) < sizeof(data))
  {
     printf("***********l'envoi a échoué**************\n>");
  }
  printf("envoie éffectué \n");
}
void startGame()
{
  if(networkinitialised!=1)
    return;
  data.dataType=GAME;
  data.car=GAME_START;
  if (SDLNet_TCP_Send(sd, &data, sizeof(data)) < sizeof(data))
  {
     printf("***********l'envoi a échoué**************\n>");
  }
  printf("envoie éffectué \n");
}
void choice()
{
  if(networkinitialised!=1)
    return;
  data.dataType=GAME;
  data.car=GAME_CHOICE;
  printf("donnez votre choix: ");
  scanf("%d",&data.from);
  if (SDLNet_TCP_Send(sd, &data, sizeof(data)) < sizeof(data))
  {
     printf("***********l'envoi a échoué**************\n>");
  }
  printf("envoie éffectué \n");
}
int isNetInitialised()
{
  return networkinitialised;
}
