/**
 * \file text.h
 * \brief élément de l'interface graphique utilisateur: le texte
 * \author Aubin Detrez
 */
#ifndef TEXT_H
#define TEXT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

/**
 * \struct Text
 * \brief Objet comprenant ce qu'il faut pour afficher du texte
 */
typedef struct
{
    SDL_Texture* texture;   /*!< données à afficher */
    SDL_Rect rect;          /*!< position et dimension */
    int size;               /*!<  rapport entre les dimension de la surface (police) et de la texture(affiché à l'écran) */
} Text;

/**
 * \fn Text createText(char str[],int x,int y,int size)
 * \brief création de la texture et paramétrage de la structure
 * \param str chaine de caractére à afficher
 * \param x position x du texte
 * \param y position y du texte
 * \param size rapport entre les dimension de la surface (police) et de la texture(affiché à l'écran)
 * \return l'objet initialisé
 */
Text createText(char str[],int x,int y,int size);
/**
 * \fn void updateText(Text* ptr,char str[])
 * \brief met à jour l'objet pour afficher la chaine str
 * \param ptr pointeur vers le texte
 * \param str chaine de caractère à afficher
 */
void updateText(Text* ptr,char str[]);
/**
 * \fn void freeText(Text *img)
 * \brief libération des ressources du texte
 * \brief pointeur vers le texte
 */
void freeText(Text *img);
/**
 * \fn void renderText(Text *img)
 * \brief affiche à l'écran le texte
 * \param texte à afficher
 */
void renderText(Text *img);
/**
 * \fn void setTextColor(int r,int g,int b)
 * \brief change la couleur du texte
 * note: tout les text créer et/ou mis à jour après auront la couleur
 * \param r taux de rouge [0,255]
 * \param g taux de vert [0,255]
 * \param b taux de bleu [0,255]
 */
void setTextColor(int r,int g,int b);

#endif

