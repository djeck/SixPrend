/**
 * \file multiText.h
 * \brief élément de l'interface graphique utilisateur: l'affichage sur plusieurs lignes
 * \author Aubin Detrez
 */
#ifndef MULTITEXT_H
#define MULTITEXT_H

#include "../Game/inc.h"
#include "text.h"
#define NB_LINE 10

/**
 * \struct MultiText
 * \brief Objet pour l'affichage sur plusieurs lignes
 */
typedef struct
{
  Text messages[NB_LINE];/*!< chaque ligne */
  char text[NB_LINE][100];/*!< chaines de caractères correspondant aux messages */
  bool update; /*!< pour une mise à jour de messages avec text dans renderMultiText */
  void (*callback)(char*); /*!< appelle le callback lors d'un click, texte sélectionné donné en parametre */
  bool initialised; /*!< true si on peut exploiter les données lors de clic false sinon */
} MultiText;

/**
 * \fn MultiText createMultiText(int x,int y)
 * \brief creation d'un texte sur plusieurs lignes
 * \param x position x de l'enssemble
 * \param y position y de l'enssemble
 * \return objet initialisé correspondant
 */
MultiText createMultiText(int x,int y);
/**
 * \fn void pushMultiText(MultiText* ptr,char *msg)
 * \brief ajout d'une ligne
 * les autres lignes vont êtres affichées plus haut
 * et dernière ligne va être perdu
 * \param ptr pointeur sur le texte
 * \param message à ajouter
 */
void pushMultiText(MultiText* ptr,char *msg);
/**
 * \fn void inputMultiText(MultiText* ptr,SDL_Event *event)
 * \brief gestion des évenement sur le texte
 * appelle la fonction callback si il y a un clic sur une ligne
 * et si initialised vaut true
 * \param ptr pointeur sur le text
 * \param event évenement à prendre en compte
 */
void inputMultiText(MultiText* ptr,SDL_Event *event);
/**
 * \fn void freeMultiText(MultiText *img)
 * \brief libére les ressources de chaques lignes
 * \param img pointeur sur le texte
 */
void freeMultiText(MultiText *img);
/**
 * \fn void renderMultiText(MultiText *img)
 * \brief affiche à l'écran toutes les lignes
 * \param pointeur sur le texte
 */
void renderMultiText(MultiText *img);

#endif
