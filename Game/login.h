/**
 * \file login.h
 * \brief Fichier correspondant à l'affichage et la gestion du login du jeu
 * \author Aubin Detrez
 *
 */

#ifndef LOGIN_H
#define LOGIN_H

#include "inc.h"
#include "../GUI/picture.h"
#include "../GUI/text.h"


/**
 * \enum Etapes
 * \brief deux etapes du login:
 */
typedef enum {
    rLog, /*!< rensseigner le nom d'utilisateur*/
    rPass/*!< rensseigner le mot de passe*/
} Etapes;

/**
 * \fn char* getUsername()
 * \return nom de l'utilisateur, NULL si non identifié
 */
char* getUsername();
/**
 * \fn void eventLogin()
 * \brief Gestion des evenements spécifique au login
 */
void eventLogin();
/**
 * \fn void initLoginRender()
 * \brief Initialisation des ressources graphiques spécifique au rendu du login
 */
void initLoginRender();
/**
 * \fn void renderLogin()
 * \brief dessine ressources graphiques spécifique au rendu du login
 */
void renderLogin();
/**
 * \fn void freeLoginRender()
 * \brief Libere les ressources graphiques initialisees par initLoginRender
 */
void freeLoginRender();
/**
 * \fn int identifier()
 * \brief Cherche dans le fichier si l'utilisateur à un compte et si le mot de passe est juste
 * \return 0 si le mot de passe est faux, 1 si l'utilisateur est bien loguer, 2 si un nouveaux compte est créé
 */
int identifier();
/**
 * \fn bool exist()
 * \brief Cherche dans le fichier si l'utilisateur à un compte ou pas
 * \return true si il est trouvé, false sinon
 */
bool exist();

#endif
