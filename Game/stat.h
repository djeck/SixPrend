/*
 * Fichier correspondant à l'affichage des statistiques
 */

#ifndef STAT_H
#define STAT_H

#include <SDL2/SDL_ttf.h>
#include <SDL_events.h>
#include <string.h>
#include "inc.h"
#define MAXSTAT 100

/*
 *La structure de statistique
 */
typedef struct {
  char nom[SIZESTR];
  int nb_vic;
  int nb_def;
} Statistique;

/*
 * la variable de la structure Statistique
 */
static Statistique stats[MAXSTAT];
/*
 * le taille de tableau
 */
static int tailleStats;
/*
 *initialisation du fichier
 */
void initFile();
/*
 * ajouter une victoire ou une défaite selon la valeur du booléen
 * true, ajouter une victoire
 * false, ajouter une défaite
 */
void ajout_stat(bool victoire);
/*
 *initialiser le tableau de statistique
 */
void loadStatFromFile();
/*
 * Gestion des evenements spécifique au statistiques
 */
void eventStat();
/*
 * Initialisation des ressources graphiques spécifique au statistiques
 */
void initStatRender();
/*
 * dessine ressources graphiques spécifique au statistiques
 */
void renderStat();
/*
 * Libere les ressources graphiques initialisees par initStatRender
 */
void freeStatRender();

#endif
