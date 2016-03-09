#include "client.h"

static IPaddress ip;		/* Server address */
static TCPsocket sd;		/* Socket descriptor */
static Data data;
static DataList dataList;
static DataGame dataGame;

static SDL_Thread *threadRecept; // thread reception

SDL_mutex *bufferLock = NULL;

static bool stopNetwork;

//SDL_cond *canRecept = NULL;
//SDL_cond *canSend = NULL;

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
    stopNetwork=false;
    bufferLock = SDL_CreateMutex();
    //canRecept = SDL_CreateCond(); 
    //canSend = SDL_CreateCond();
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
    int cnt;
    callback = ptr;
    
    while(!stopNetwork)
    {
    //SDL_CondWait( canRecept, bufferLock );
    cnt = SDLNet_TCP_Recv(sd, &data, sizeof(Data));
    //SDL_mutexP( bufferLock );
    (*callback)(&data);
    //SDL_mutexV( bufferLock );
    }
    //SDL_CondSignal( canSend );
    printf("Treception terminé\n");
    return cnt;
}

void reception(void (*callback)(Data*))
{
  
  if(networkinitialised!=1)
    return;
  threadRecept = SDL_CreateThread(Treception, "receptData", (void *)callback);
  if (NULL == threadRecept) {
        printf("\nSDL_CreateThread failed: %s\n", SDL_GetError());
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
    printf("freeRessourcesReseau: ERROR\n");
    return;
  }
  int threadReturnValue;
  stopNetwork=true;
  printf("Waiting for reception thread\n");
  SDL_WaitThread(threadRecept, &threadReturnValue);
  printf("\nThread returned value: %d\n", threadReturnValue);
  SDL_DestroyMutex( bufferLock );
  //SDL_DestroyCond( canSend );
  //SDL_DestroyCond( canRecept );
  
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
