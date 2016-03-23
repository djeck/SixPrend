#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <SDL2/SDL_net.h>
#include "network.hpp"

//fonction de base
void initialisation(int argc, char **argv);
void freeRessources();

void wait();

//reception
void receptList();
void receptGame();
void reception();

//emission
void sendMsg();
void askList();
void join();
void create();
void startGame();
void choice();




#endif
