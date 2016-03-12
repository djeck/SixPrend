#ifndef CLIENT_H
#define CLIENT_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL_net.h>
#include <SDL2/SDL_thread.h>
#include <SDL2/SDL_timer.h>
#include "network.h"
#define PORT 2000

//fonction de base
void initialisationReseau(char *strip,void (*backData)(Data*),void (*backList)(DataList*),void (*backGame)(DataGame*));
void updateCallback(void (*backData)(Data*),void (*backList)(DataList*),void (*backGame)(DataGame*));
void freeRessourcesReseau();

//reception début de la boucle (dans un nouveau SDL_thread
void reception();

//emission
void sendMsg(char *msg);
void askList();
void join(char* str,int passwd);
void sendQuit();
void create(char* str,int passwd);
void startGame();
void choice(int choice);

int isNetInitialised();

void printData();
void setWait(bool arg0);


#endif
