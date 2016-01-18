/*
 * Fichier correspondant à l'affichage et la gestion du login dun jeu
 */

#ifndef LOGIN_H
#define LOGIN_H

#define BACKGROUNDPATH "./media/background.bmp" // fond d'ecran
#define FONTPATH "./media/sixty.fon" // fichier de fnnt
#define FILELOGIN "./media/login.txt"
#define SIZESTR 21
#define FONTSIZE 256 // taille maximale chagé depuis le fichier de font

#include <SDL2/SDL_ttf.h>
#include <string.h>
#include "inc.h"
#include "cocoa.h"

/*
 * deux etapes du login:
 * rLog : rensseigner le nom d'utilisateur
 * rPass : rensseigner le mot de passe
 */
typedef enum{rLog,rPass} Etapes;

static Etapes step;

// donnees à afficher
static char text[SIZESTR];

/*
 * Gestion des evenements spécifique au login
 * agis sur la variable globale terminer
 */
void eventLogin();
/*
 * Initialisation des ressources graphiques spécifique au rendu du login
 * necessite la variable renderer
 */
void initLoginRender();
/*
 * Met à jour la texture du texte avec la chaine de charactere str
 */
void updateText(char str[]);
/*
 * dessine ressources graphiques spécifique au rendu du login
 * necessite la variable renderer
 */
void renderLogin();
/*
 * Libere les ressources graphiques initialisees par initLoginRender
 */
void freeLoginRender();
/*
 * Cherche dans le fichier si l'utilisateur à un compte et si le mot de passe est juste
 * retourn 0 si le mot de passe est faux
 * return 1 si l'utilisateur est bien loguer
 * return 2 si un nouveaux compte est créé
 */
int identifier(char usernm[],char passwd[]);

#endif
