 /**
 * \file animCard.h
 * \brief Composant de l'interface graphique utilisateur: la carte avec animation
 * La carte se d�place selon une �quation pr�-d�finie
 * \author Aubin Detrez
 */
#ifndef ANIM_CARD_HH
#define ANIM_CARD_HH

#include "../Game/inc.h"
#include "card.h"

#define VITESSE 100 // temps en millisecond pour terminer

/**
 * \struct AnimCard
 * \brief information de base pour les cartes du jeu qui se d�placent
 */
typedef struct
{
    SDL_Rect rect; /*!< position et dimenssion de la carte*/
    int id; /*!< num�ro de la carte, compris entre 0 et 104, 0 si non affich� */

    int xi,yi,xf,yf; /*!< position initial et position finale */
    Uint32 time; /*!< gere le temps pour une vitesse contante */
    bool isMoving; /*!< vaut true si la carte est en d�placement */
    bool fin; /*!< toutes les cartes sont arriv�ent � destination, on peut afficher le jeu */

    int compteur; /*!< permet de savoir quelles cartes ont a d�j� plac�ent */
} AnimCard;

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

