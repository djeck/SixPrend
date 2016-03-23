/**
 * \file client.c
 * \brief implémentation réseau
 * \author Aubin Detrez
 *
 * Permet de ce connecter au serveur de jeu, lancer un thread
 * d'écoute et recevoir les données du serveur pas l'intermédiaire de callback
 *
 */

#include "client.h"

static IPaddress ip;		  /* adresse du serveur */
static TCPsocket sd;		  /* socket tcp */

static void (*mCData)(Data*);       /* callback appellé par le thread de réception*/
static void (*mCList)(DataList*);   /* callback pour les listes de salles */
static void (*mCGame)(DataGame*);   /* callback pour les données de jeu */

static SDL_Thread *threadRecept; // thread de réception

static SDL_mutex *bufferLock = NULL;
/*
 * fait patienter le thread de réception jusqu'à ce que le thread de réception
 * jusqu'à ce que le thread principale puisse traiter les retours (callback valide)
 */
static bool waiting;

static int networkinitialised = 0; // s'assure que tout est déjà initialisé

void initialisationReseau(char *strip,void (*backData)(Data*),void (*backList)(DataList*),void (*backGame)(DataGame*))
{

    mCData = backData;
    mCList= backList;
    mCGame= backGame;
    printf("initialisationReseau: test\n");
    if(isNetInitialised())
    {
        printf("initialisationReseau: réseau djà initialisé: libération des ressources\n");
        sendQuit();
        printf("Waiting for reception thread to reconnect\n");
        int threadReturnValue;
        SDL_WaitThread(threadRecept, &threadReturnValue);
        printf("\nThread returned value: %d\n", threadReturnValue);
        SDLNet_TCP_Close(sd);
    }
    else
    {
    if (SDLNet_Init() < 0)
    {
        printf("SDLNet_Init: %s\n", SDLNet_GetError());
        return;
    }
    bufferLock = SDL_CreateMutex();
    }
    /* Resolve the host we are connecting to */
    if (SDLNet_ResolveHost(&ip, strip, PORT) < 0)
    {
        printf("Can't resolve host: %s\n", SDLNet_GetError());
        return;
    }

    /* Open a connection with the IP provided (listen on the host's port) */
    if (!(sd = SDLNet_TCP_Open(&ip)))
    {
        printf("Can't open tcp connecting: %s\n", SDLNet_GetError());
        return;
    }


    if(!bufferLock)
    {
        printf("initialisationReseau: ERROR can't create mutex\n");
    }
    //canRecept = SDL_CreateCond();
    //canSend = SDL_CreateCond();
    networkinitialised = 1;
}
void updateCallback(void (*backData)(Data*),void (*backList)(DataList*),void (*backGame)(DataGame*))
{
    //SDL_LockMutex( bufferLock ); // lock
    mCData = backData;
    mCList= backList;
    mCGame= backGame;
    //SDL_UnlockMutex( bufferLock ); // unlock
}
static int Treception(void *ptr)
{
    Data data;                /* buffer de réception */
    DataList dataList;        /* buffer de réception pour les listes de salles*/
    DataGame dataGame;        /* buffer de réception pour les données de jeu*/

    int cnt;
    bool stopNetwork=false;

    while(!stopNetwork)
    {
        cnt = SDLNet_TCP_Recv(sd, &data, sizeof(Data));
        if(cnt <= 0)
            return cnt;
        (*mCData)(&data);
        if(data.dataType == CONN)
        {
            if(data.car == SWITCH) // on nous prévient que une dataList va être transmise
            {
                do
                {
                    cnt = SDLNet_TCP_Recv(sd, &dataList, sizeof(DataList));
                    (*mCList)(&dataList);

                }
                while(cnt>0 && !dataList.end);
            }
            else if(data.car == CONN_QUIT)
                stopNetwork = true;
            else if(data.car == CONN_ERROR)
                stopNetwork=true;
            else if(data.car == CONN_STOP)
                stopNetwork=true;

        }
        else if(data.dataType == GAME)
        {
            if(data.car == SWITCH) // on nous prévient que une dataGame va être transmise
            {
                if(waiting)
                {
                    printf("reception thread is waiting main thread to switch to game\n");
                    while(waiting){}
                }
                cnt = SDLNet_TCP_Recv(sd, &dataGame, sizeof(DataGame));
                (*mCGame)(&dataGame);
            }
            else if(data.car == GAME_ERROR)
            {
                stopNetwork=true;
            }
        }
        if(cnt <= 0)
            stopNetwork=true;
    }
    printf("Treception terminé\n");
    return cnt;
}

void reception()
{
    waiting=false;
    if(networkinitialised!=1)
        return;
    threadRecept = SDL_CreateThread(Treception, "receptData", (void *)NULL);
    if (NULL == threadRecept)
    {
        printf("\nSDL_CreateThread failed: %s\n", SDL_GetError());
    }
}

void sendMsg(char *msg)
{
    Data data;
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
    Data data;
    if(networkinitialised!=1)
        return;
    data.dataType=CONN;
    data.car=CONN_LIST;
    data.from=-1;
    if (SDLNet_TCP_Send(sd, &data, sizeof(data)) < sizeof(data))
    {
        printf("***********l'envoi a échoué**************\n>");
    }
    printf("envoie éffectué \n");
}
void join(char* str,int passwd)
{
    Data data;
    if(networkinitialised!=1)
        return;
    data.dataType=CONN;
    data.car=CONN_JOIN;
    strcpy(data.tab,str);
    data.from = passwd;
    if (SDLNet_TCP_Send(sd, &data, sizeof(data)) < sizeof(data))
    {
        printf("***********l'envoi a échoué**************\n>");
    }
    printf("envoie éffectué \n");
}
void create(char* str,int passwd)
{
    Data data;
    if(networkinitialised!=1)
        return;
    data.dataType=CONN;
    data.car=CONN_CREATE;
    strcpy(data.tab,str);
    data.from = passwd;
    if (SDLNet_TCP_Send(sd, &data, sizeof(data)) < sizeof(data))
    {
        printf("***********l'envoi a échoué**************\n>");
    }
    printf("envoie éffectué \n");
}
void startGame()
{
    Data data;
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
void choice(int choice)
{
    Data data;
    if(networkinitialised!=1)
        return;
    data.dataType=GAME;
    data.car=GAME_CHOICE;
    data.from=choice;
    if (SDLNet_TCP_Send(sd, &data, sizeof(data)) < sizeof(data))
    {
        printf("***********l'envoi a échoué**************\n>");
    }
    printf("envoie éffectué \n");
}
void sendQuit()
{
    Data data;
    if(networkinitialised!=1)
        return;
    data.dataType=CONN;
    data.car=CONN_QUIT;
    data.from=0;
    if (SDLNet_TCP_Send(sd, &data, sizeof(data)) < sizeof(data))
    {
        printf("***********l'envoi a échoué**************\n>");
    }
    printf("envoie éffectué \n");
}

void freeRessourcesReseau()
{
    if(networkinitialised!=1)
    {
        printf("freeRessourcesReseau: ERROR\n");
        return;
    }
    int threadReturnValue;
    sendQuit();
    printf("Waiting for reception thread\n");
    SDL_WaitThread(threadRecept, &threadReturnValue);
    printf("\nThread returned value: %d\n", threadReturnValue);
    SDLNet_TCP_Close(sd);
    SDL_DestroyMutex( bufferLock );
    //SDL_DestroyCond( canSend );
    //SDL_DestroyCond( canRecept );

    SDLNet_Quit();
    networkinitialised=0;
}
int isNetInitialised()
{
    return networkinitialised;
}
void setWait(bool arg0)
{
    waiting = arg0;
}
void printData(Data* data)
{
    if(data->dataType == CONN)
    {
        printf("données de type CONN reçu\n");

        if(data->car == CONN_FULL)
            printf("CONN_FULL Echec de la connection: serveur plein\n");
        else if(data->car == CONN_OK)
            printf("CONN_OK Connection etablie avec success\n");
        else if(data->car == CONN_STOP)
            printf("CONN_STOP le serveur met fin à la connection\n");
        else if(data->car == CONN_ERROR)
            printf("CONN_ERROR erreur inconnue\n");
        else if(data->car == CONN_LIST)
            printf("CONN_LIST ne devrais pas etre envoyé au client\n");
        else if(data->car == CONN_JOIN)
            printf("CONN_JOIN ne devrais pas etre envoyé au client\n");
        else if(data->car == CONN_CREATE)
            printf("CONN_CREATE ne devrais pas etre envoyé au client\n");
        else if(data->car == SWITCH)
            printf("SWITCH le serveur va envoyer des datalists\n");
        else if(data->car == CONN_QUIT)
            printf("CONN_QUIT le serveur dit au client de quitter\n");
        else
            printf("donnees de nature inconnue\n");
    }
    else if(data->dataType == MSG)
    {
        printf("données de type MSG reçu\n");
    }
    else if(data->dataType == GAME)
    {
        printf("données de type GAME reçu\n");
        if(data->car == GAME_OK)
            printf("GAME_OK bien connecté à une salle\n");
        else if(data->car == GAME_LOGIN)
            printf("GAME_LOGIN le serveur demande d'envoyer le login\n");
        else if(data->car == GAME_ERROR)
            printf("GAME_ERROR erreur\n");
        else if(data->car == GAME_START)
            printf("GAME_START on peut commencer à jouer\n");
        else if(data->car == GAME_CHOICE)
            printf("GAME_CHOICE le serveur demande aux joueurs de choisir leurs cartes\n");
        else if(data->car == END_TURN)
            printf("END_TURN fin du tour, apprêté vous à recevoir les donnees du jeu\n");
        else if(data->car == END_GAME)
            printf("END_GAME fin du jeu, attend game_start pour recommancer\n");
        else if(data->car == SWITCH)
            printf("SWITCH le serveur va envoyer des dataGames\n");
        else
            printf("donnees de nature inconnue\n");
    }
    else
        printf("ERROR type de donné inconu\n");

    printf("***************************\n");
    printf("datatype: %d\n",(int)data->dataType);
    printf("car: %d\n",(int)data->car);
    printf("tab: <<%s>>\n",data->tab);
    printf("from: %d\n",data->from);
    printf("***************************\n");
}

void identifySrv(char *name)
{
    Data buff;
    if(networkinitialised!=1)
        return;
    buff.dataType=GAME;
    buff.car=GAME_LOGIN;
    buff.from=0;
    strcpy(buff.tab,name);
    if (SDLNet_TCP_Send(sd, &buff, sizeof(Data)) < sizeof(Data))
    {
        printf("***********l'envoi a échoué**************\n>");
    }
    printf("envoie demande identification\n");
}
