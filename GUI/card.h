 /**
 * \file card.h
 * \brief Composant de l'interface graphique ustilisateur: la carte
 * \author Aubin Detrez
 */
#ifndef CARD_HH
#define CARD_HH

#include "../Game/inc.h"

#define NB_CARD 104
#define PATH_CARD "./media/%d.bmp"
#define CARD_H 80
#define CARD_W 52

/**
 * \struct Card
 * \brief information de base pour les cartes du jeu
 */
typedef struct
{
    SDL_Rect rect; /*!< position et dimenssion de la carte*/
    int id; /*!< numéro de la carte, compris entre 0 et 104, 0 si non affiché */
    bool selected; /*!< la carte est mise en évidence (si selectionnée par le joueur)*/
} Card;

/**
 * \fn void initCard()
 * \brief initialisation des ressources graphiques pour les cartes
 * les ressources sont les mêmes quelques soit le nombre de carte qui seront affichées
 */
void initCard();
/**
 * \fn void renderCard(Card* card)
 * \brief afficher à l'écran une carte
 * l'image affichée est choisit selon le numéro de la carte depuis
 * les textures chargées par initCard
 * \param card pointeur vers la carte à afficher
 */
void renderCard(Card* card);
/**
 * \fn void eventCard(SDL_Event *event,Card* card,void (*callback)(int))
 * \brief gére les événement sur une carte
 * si une carte est cliquée la fonction appelle le callback avec le numéro
 * de la carte en paramètre.
 * \param event pointeur vers l'évenement à prendre en compte
 * \param card pointeur vers la carte
 * \param callback pointeur vers la fonction à appeler en cas de clic
 */
void eventCard(SDL_Event *event,Card* card,void (*callback)(int));
/**
 * \fn void detroyCard()
 * \brief libére les ressources chargées dans initCard
 */
void detroyCard();

#endif
