/**
 * \file button.h
 * \brief élément de l'interface graphique utilisateur: le bouton
 * \author Aubin Detrez
 */
#ifndef BUTTON_H
#define BUTTON_H

#include "../Game/inc.h"
#define SIZESTR 21

/**
 * \struct Button
 * \brief élément graphique, cliquable
 */
typedef struct
{
    SDL_Texture* texture; /*!< texture que l'on affiche à l'écran */
    SDL_Texture* selTexture; /*!< texture pour le bouton selectionné */
    SDL_Rect rect; /*!< position et dimension du bouton */

    bool select; /*!< si le bouton change de texture*/
    int size; /*!< rapport entre la taille de la surface (dépend de la police) et la texture (entre 10 et 5) */
    void (*callback)(void); /*!< callback appelé lors d'un clic sur rect*/
} Button;

/**
 * \fn Button createButton(char str[],int x,int y,int size)
 * \brief creer les ressources du bouton
 * Attention le callback n'est pas initialisé
 * \param str contenu du bouton (chaine de caractère)
 * \param x position x du bouton
 * \param y position y du bouton
 * \param size rapport entre la taille de la surface (dépend de la police) et la texture
 * \return l'objet initialisé
 */
Button createButton(char str[],int x,int y,int size);
/**
 * \fn void inputButton(Button* ptr,SDL_Event *event)
 * \brief gére les évenement sur le bouton
 * \param ptr pointeur sur le bouton
 * \param event variable contenant l'événement à prendre en compte
 */
void inputButton(Button* ptr,SDL_Event *event);
/**
 * \fn void renderButton(Button *img)
 * \brief affiche le bouton sur l'écran
 * \param img pointeur sur le bouton
 */
void renderButton(Button *img);
/**
 * \fn void freeButton(Button *img)
 * \brief libére les ressources graphiques de l'élément
 * \param img pointeur sur le bouton
 */
void freeButton(Button *img);


#endif
