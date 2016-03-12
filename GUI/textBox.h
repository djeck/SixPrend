 /**
 * \file textBox.h
 * \brief élément de l'interface graphique utilisateur: la saisie de texte
 * \author Aubin Detrez
 */
#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

/**
 * \struct textBox
 * \brief regroupement de composants graphiques pour faire de la saisie de texte
 */
typedef struct
{
    SDL_Texture* texture; /*!< donnée à afficher */
    SDL_Rect rect;
    SDL_Rect maxRect; /*!< cadre noir pour délimiter la zone de saisie */

    SDL_Rect rBar; /*!< rectangle de la barre clignotante */

    bool select; /*!< si la text box capture la saisie et affiche la bare clignotante */

    char text[100]; /*!<  */
    int maxcar; /*!< nombre maximum de caractére */
    int wLettre; /*!< largeur d'une lettre (maximale)*/
} TextBox;

/**
 * \fn TextBox createTextBox(char str[],int x,int y,int w,int h,int maxcar,bool arg0)
 * \brief creation d'une zone de saisie de texte
 * \param str chaine de caractere du contenu à afficher
 * \param x position x
 * \param y position y
 * \param w largeur en pixel d'un caractére
 * \param h hauteur de chaque caractéres
 * \param maxcar nombre maximum de caractére saisie
 * \param arg0 si true la zone de saisie est selectionnée par default
 * \return l'objet initialisé
 */
TextBox createTextBox(char str[],int x,int y,int w,int h,int maxcar,bool arg0); // arg0: selected or not by default, h et w dimenssion de chaque lettre
/**
 * \fn void updateTextBox(TextBox* ptr)
 * \brief mise à jour d'une zone de saisie de texte
 * note: à partir de la variable text
 * \param ptr pointeur sur l'objet
 */
void updateTextBox(TextBox* ptr);
/**
 * \fn void inputTextBox(TextBox* ptr,SDL_Event *event)
 * \brief gére les entrée pour la saisie de texte
 * pour qu'il y ait saisie la zone doit être sélectionnée soit par un clic sur maxRect
 * ou par default
 * \param ptr pointeur sur l'objet
 * \param event évenement à prendre en compte
 */
void inputTextBox(TextBox* ptr,SDL_Event *event); // si select==true gére la saisie de caractères
/**
 * \fn void inputPassBox(TextBox* ptr,SDL_Event *event)
 * \brief gére les entrée pour la saisie de mot de passe
 * pour qu'il y ait saisie la zone doit être sélectionnée soit par un clic sur maxRect
 * ou par default
 * la variable text contient le mot de passe à tout instant mais la texture ne comprend
 * que des étoiles
 * \param ptr pointeur sur l'objet
 * \param event évenement à prendre en compte
 */
void inputPassBox(TextBox* ptr,SDL_Event *event); // afficher des étoiles
/**
 * \fn void freeTextBox(TextBox *img)
 * \brief libére les ressources utilisées par la zone de saisie de texte
 * \param img pointeur sur l'objet
 */
void freeTextBox(TextBox *img);
/**
 * \fn void renderTextBox(TextBox *img)
 * \brief afficher la saisie de texte à l'écran
 * \param img pointeur sur l'objet
 */
void renderTextBox(TextBox *img);

#endif
