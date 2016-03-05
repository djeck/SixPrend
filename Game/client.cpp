#include "client.hpp"

static IPaddress ip;		/* Server address */
static TCPsocket sd;		/* Socket descriptor */
static int quit, len;
static Data data;
static DataList dataList;
static DataGame dataGame;

void initialisation(int argc, char **argv)
{
    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s host port\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (SDLNet_Init() < 0)
    {
        fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
        exit(EXIT_FAILURE);
    }

    /* Resolve the host we are connecting to */
    if (SDLNet_ResolveHost(&ip, argv[1], atoi(argv[2])) < 0)
    {
        fprintf(stderr, "SDLNet_ResolveHost: %s\n", SDLNet_GetError());
        exit(EXIT_FAILURE);
    }

    /* Open a connection with the IP provided (listen on the host's port) */
    if (!(sd = SDLNet_TCP_Open(&ip)))
    {
        fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError());
        exit(EXIT_FAILURE);
    }
}


void receptList()
{
  std::cout<<"reception d'une liste"<<std::endl;
  int receivedByteCount = SDLNet_TCP_Recv(sd, &dataList, sizeof(DataList));
  std::cout<<"***************************"<<std::endl;
  std::cout<<"tab: <<"<<dataList.tab<<">>"<<std::endl;
  std::cout<<"end: "<<dataList.end<<std::endl;
  std::cout<<"***************************"<<std::endl;
}

void receptGame()
{
  
  std::cout<<"reception de donnée de jeu"<<std::endl;
  int receivedByteCount = SDLNet_TCP_Recv(sd, &dataGame, sizeof(DataGame));
  std::cout<<"***************************"<<std::endl;
  std::cout<<"table: "<<std::endl;
  for(int i=0;i<4;i++)
  {
    for(int z=0;z<6;z++)
      std::cout<<dataGame.table[i][z]<<" ";
    std::cout<<std::endl;
  }
  for(int i=0;i<10;i++)
    std::cout<<"users "<<i<<": <<"<<dataGame.users[i]<<">>"<<std::endl;
  for(int i=0;i<10;i++)
    std::cout<<"turn "<<i<<": "<<dataGame.turn[i]<<std::endl;
  for(int i=0;i<10;i++)
    std::cout<<"scores "<<i<<": "<<dataGame.scores[i]<<std::endl;
  for(int i=0;i<10;i++)
    std::cout<<"hand "<<i<<": "<<dataGame.hand[i]<<std::endl;
  std::cout<<"***************************"<<std::endl;
}

void reception()
{
    int receivedByteCount = SDLNet_TCP_Recv(sd, &data, sizeof(Data));
    if(data.dataType == CONN)
    {
      std::cout<<"données de type CONN reçu"<<std::endl;
      
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
	std::cout<<"données de type MSG reçu"<<std::endl;
    }
    else if(data.dataType == GAME)
    {
      std::cout<<"données de type GAMME reçu"<<std::endl;
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
      std::cout<<"ERROR type de donné inconu"<<std::endl;
    
    std::cout<<"***************************"<<std::endl;
    std::cout<<"datatype: "<<(int)data.dataType<<std::endl;
    std::cout<<"car: "<<(int)data.car<<std::endl;
    std::cout<<"tab: <<"<<data.tab<<">>"<<std::endl;
    std::cout<<"from: "<<data.from<<std::endl;
    std::cout<<"***************************"<<std::endl;
}

void sendMsg()
{
  std::cout<<"give a msg to send >";
  data.dataType=MSG;
  scanf("%s", data.tab);
  if (SDLNet_TCP_Send(sd, &data, sizeof(data)) < sizeof(data))
  {
     printf("***********l'envoi a échoué**************\n>");
  }
  std::cout<<"envoie éffectué \n";
}
void askList()
{
  data.dataType=CONN;
  data.car=CONN_LIST;
  if (SDLNet_TCP_Send(sd, &data, sizeof(data)) < sizeof(data))
  {
     printf("***********l'envoi a échoué**************\n>");
  }
  std::cout<<"envoie éffectué \n";
}
void wait()
{
  std::cout<<"press enter to continue\n";
  fflush(stdin);
  getchar();
}
void freeRessources()
{
  SDLNet_TCP_Close(sd);
  SDLNet_Quit();
}
void join()
{
  std::cout<<"envoie une demande pour rejoindre une salle \n";
  data.dataType=CONN;
  data.car=CONN_JOIN;
  std::cout<<"saississez le nom de la salle \n";
  scanf("%s",data.tab);
  std::cout<<"saississez le mot de passe -1 sinon \n";
  scanf("%d",&data.from);
  if (SDLNet_TCP_Send(sd, &data, sizeof(data)) < sizeof(data))
  {
     printf("***********l'envoi a échoué**************\n>");
  }
  std::cout<<"envoie éffectué \n";
}
void create()
{
  std::cout<<"envoie une demande pour creer une salle \n";
  data.dataType=CONN;
  data.car=CONN_CREATE;
  std::cout<<"saississez le nom de la salle \n";
  scanf("%s",data.tab);
  std::cout<<"saississez le mot de passe -1 sinon \n";
  scanf("%d",&data.from);
  if (SDLNet_TCP_Send(sd, &data, sizeof(data)) < sizeof(data))
  {
     printf("***********l'envoi a échoué**************\n>");
  }
  std::cout<<"envoie éffectué \n";
}
void startGame()
{
  data.dataType=GAME;
  data.car=GAME_START;
  if (SDLNet_TCP_Send(sd, &data, sizeof(data)) < sizeof(data))
  {
     printf("***********l'envoi a échoué**************\n>");
  }
  std::cout<<"envoie éffectué \n";
}
void choice()
{
  data.dataType=GAME;
  data.car=GAME_CHOICE;
  std::cout<<"donnez votre choix: ";
  scanf("%d",&data.from);
  if (SDLNet_TCP_Send(sd, &data, sizeof(data)) < sizeof(data))
  {
     printf("***********l'envoi a échoué**************\n>");
  }
  std::cout<<"envoie éffectué \n";
}
