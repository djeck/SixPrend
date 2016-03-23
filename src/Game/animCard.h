 /**
 * \file animCard.h
 * \brief Composant de l'interface graphique utilisateur: la carte avec animation
 * La carte se d�place selon une �quation pr�-d�finie
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
 * \brief initialisation des ressources graphiques pour les cartes anim�es
 */
void initAnimCard();
/**
 * \fn void updateAnimCard(DataGame* data)
 * \brief met � jour l'affichage avec les donn�e le paquet
 * note: doit �tre apell� par le thread principale
 * \param data paquet contenant les donn�es
 */
void updateAnimCard(DataGame* data);
/**
 * \fn void renderAnimCard(Card* card)
 * \brief afficher � l'�cran une carte
 */
void renderAnimCard();
/**
 * \fn void destroyCard()
 * \brief lib�re les ressources charg�es dans initAnimCard
 */
void destroyAnimCard();

#endif

