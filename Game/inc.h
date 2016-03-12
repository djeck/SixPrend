/**
 * \file inc.h
 * \brief macro et function utiles partout
 * \author Aubin Detrez
 * centralise les macros et inclusions utilisees dans plusieurs parties du projet
 */
#ifndef INC_H
#define INC_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "login.h"
#include "menu.h"
#include "game.h"
#include "mode.h"
#include "stat.h"

#define FILELOGIN "./media/login.txt"
#define BACKGROUNDPATH "./media/background.bmp" // fond d'ecran
#define SCREEN_WIDTH 800 // largeur par default de la fenetre
#define SCREEN_HEIGHT 480 // hauteur par default de la fenetre
#define SIZESTR 21 // taille par default du nom
#define FONTPATH "./media/arial.ttf" // fichier de font
#define FONTSIZE 256 // taille maximale chagé depuis le fichier de font
#define CLIGNE 500 // durée en milliseconde du clignotement du curseur (cf textBox.h)

/**
 * \enum MainStep
 * \brief étapes principales du jeu
 * elles correspondent à des fonctions de rendus ... particulières (cf inc.c, main.c)
 */
typedef enum {
    none, /*!< êtat de base, pas de ressources propres */
    login, /*!< l'utilisateur est invité à s'identifier*/
    menu, /*!< choix entre diférentes étapes */
    mode, /*!< choix des paramêtre éssentiellement réseau*/
    stat, /*!< affichage des statistiques du joueur */
    game, /*!< jeu */
    end /*!< libération des ressources et fin de l'application */
} MainStep;

/*
 * Les variables globales
 * ne doivent êtres utilisées que depuis le thread principal
 */

TTF_Font* font; // initialisé par init()
SDL_Window * window; // initialisé par init()
SDL_Renderer * renderer; // initialisé par init()
MainStep globalStep;// Etapes principale du jeu

/**
 * \fn void changeStep(MainStep nextStep)
 * \brief permet de mettre à jour l'étape principale
 * initialise et libere les ressources
 * \param nextStep étape principale suivante
*/
void changeStep(MainStep nextStep);

/**
 * \fn bool collisionWithMouse(SDL_Rect arg0,int mx,int my)
 * \brief gére les collision de la souris avec un rectangle
 * peut s'appliqué à tout point
 * \param arg0 hitbox du rectangle
 * \param mx position x de la souris (ou du point)
 * \param my position y de la souris (ou du point)
 * \return true s'il y a collision, false sinon
*/
bool collisionWithMouse(SDL_Rect arg0,int mx,int my);

#endif
