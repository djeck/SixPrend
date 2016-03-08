#ifndef CLIENT_H
#define CLIENT_H

#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL_net.h>
#include "network.h"
#define PORT 2000

//fonction de base
void initialisationReseau(char *strip);
void freeRessourcesReseau();

void wait();

//reception
DataList* receptList();
void receptGame();
void reception();

//emission
void sendMsg();
void askList();
void join();
void create();
void startGame();
void choice();

int isNetInitialised();




#endif
