 /**
 * \file animCard.h
 * \brief Composant de l'interface graphique utilisateur: la carte avec animation
 * La carte se déplace selon une équation pré-définie
 * \author Aubin Detrez
 */
#ifndef ANIM_CARD_HH
#define ANIM_CARD_HH

#include "../Game/inc.h"
#include "card.h"

#define VITESSE 100 // temps en millisecond pour terminer

/**
 * \struct AnimCard
 * \brief information de base pour les cartes du jeu qui se déplacent
 */
typedef struct
{
    SDL_Rect rect; /*!< position et dimenssion de la carte*/
    int id; /*!< numéro de la carte, compris entre 0 et 104, 0 si non affiché */

    int xi,yi,xf,yf; /*!< position initial et position finale */
    Uint32 time; /*!< gere le temps pour une vitesse contante */
    bool isMoving; /*!< vaut true si la carte est en déplacement */
    bool fin; /*!< toutes les cartes sont arrivéent à destination, on peut afficher le jeu */

    int compteur; /*!< permet de savoir quelles cartes ont a déjà placéent */
} AnimCard;

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

