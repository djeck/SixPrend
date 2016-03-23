/**
 * \file stat.h
 * \brief affichage et gestions des statistiques
 * \author Aubin Detrez et Zongwei WU
 *
 */
#ifndef STAT_H
#define STAT_H

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_events.h>
#include <string.h>

#include "login.h"
#include "../GUI/button.h"
#include "../GUI/text.h"
#include "../GUI/picture.h"

#define MAXSTAT 100 // nombre de statistiques maximum lus depuis le fichier FILESTATS
#define FILESTATS "./media/stats.txt"

/**
 * \struct Statistique
 * \brief donnée de base des statistiques
 */
typedef struct
{
    char nom[SIZESTR]; /*!< nom du joueur */
    int nb_vic; /*!< nombre de victoire */
    int nb_def; /*!< nombre de défaite */
} Statistique;

/**
 * \fn void ajout_stat(bool victoire)
 * \brief ajouter une victoire ou une défaite selon la valeur du booléen
 * \param victoire true, ajouter une victoire, false une défaite
 */
void ajout_stat(bool victoire);
/**
 * \fn void loadStatFromFile()
 * \brief charge le tableau de statistique
 */
void loadStatFromFile();
/**
 * \fn void eventStat()
 * \brief Gestion des evenements spécifique au statistiques
 */
void eventStat();
/**
 * \fn void initStatRender()
 * \brief Initialisation des ressources graphiques spécifique au statistiques
 */
void initStatRender();
/**
 * \fn void renderStat()
 * \brief dessine ressources graphiques spécifique au statistiques
 */
void renderStat();
/**
 * \fn void freeStatRender()
 * \brief Libere les ressources graphiques initialisees par initStatRender
 */
void freeStatRender();

#endif
