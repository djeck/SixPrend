 /**
 * \file animCard.h
 * \brief Composant de l'interface graphique utilisateur: la carte avec animation
 * La carte se déplace selon une équation pré-définie
 * \author Aubin Detrez
 */
#ifndef ANIM_CARD_HH
#define ANIM_CARD_HH

#include "../Network/network.h"
#include "../GUI/card.h"

#define VITESSE 1000.0f // temps en millisecond pour terminer
#define K 5.0f


/**
 * \fn void initAnimCard()
 * \brief initialisation des ressources graphiques pour les cartes animées
 */
void initAnimCard();
/**
 * \fn void updateAnimCard(DataGame* data)
 * \brief met à jour l'affichage avec les donnée le paquet
 * note: doit être apellé par le thread principale
 * \param data paquet contenant les données
 */
void updateAnimCard(DataGame* data);
/**
 * \fn void renderAnimCard(Card* card)
 * \brief afficher à l'écran une carte
 */
void renderAnimCard();
/**
 * \fn void destroyCard()
 * \brief libére les ressources chargées dans initAnimCard
 */
void destroyAnimCard();

#endif

