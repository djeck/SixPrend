#ifndef CLIENT_H
#define CLIENT_H

#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL_net.h>
#include <SDL2/SDL_thread.h>
#include <SDL2/SDL_timer.h>
#include "network.h"
#define PORT 2000

//fonction de base
void initialisationReseau(char *strip);
void freeRessourcesReseau();

//reception
void reception(void (*callback)(Data*));

//emission
void sendMsg(char *msg);
void askList();
void join();
void create();
void startGame();
void choice();

int isNetInitialised();




#endif
