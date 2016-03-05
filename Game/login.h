/*
 * Fichier correspondant à l'affichage et la gestion du login du jeu
 */

#ifndef LOGIN_H
#define LOGIN_H

#include "inc.h"
#include "../GUI/textBox.h"
#include "../GUI/picture.h"
#include "../GUI/text.h"


/*
 * deux etapes du login:
 * rLog : rensseigner le nom d'utilisateur
 * rPass : rensseigner le mot de passe
 */
typedef enum {rLog,rPass} Etapes;

// retourne NULL si non identifier
char* getUsername();
/*
 * Gestion des evenements spécifique au login
 */
void eventLogin();
/*
 * Initialisation des ressources graphiques spécifique au rendu du login
 * necessite la variable renderer
 */
void initLoginRender();
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
int identifier();
/*
 * Cherche dans le fichier si l'utilisateur à un compte ou pas
 * return true si il est trouvé, false sinon
 */
bool exist();

#endif
