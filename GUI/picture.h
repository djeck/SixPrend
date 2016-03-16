/**
 * \file picture.h
 * \brief Composant de l'interface graphique utilisateur: l'image
 * \author Aubin Detrez
 */
#ifndef PICTURE_H
#define PICTURE_H

#include "../Game/inc.h"

/**
 * \struct Picture
 * \brief Object contenant toutes les informations n�cessaires d'une image
 */
typedef struct
{
    SDL_Texture* texture;   /*!< donn�es affich�es */
    SDL_Rect rect;          /*!< position et dimenssion de l'image */
} Picture;

/**
 * \fn Picture createPicture(char path[],int x,int y,int size)
 * \brief creer l'image
 * \param path chemin vers le fichier de l'image (format bitmap)
 * \param x position x de l'image
 * \param y position y de l'image
 * \param size rapport entre les dimenssion de l'image charg� et celles souhait�es
 * \return l'image initialis�e
 */
Picture createPicture(char path[],int x,int y,int size);
/**
 * \fn void freePicture(Picture *img)
 * \brief lib�rer les ressources graphiques
 * \param img pointeur sur l'image
 */
void freePicture(Picture *img);
/**
 * \fn void renderPicture(Picture *img)
 * \brief afficher � l'�cran l'image
 * \param img pointeur sur l'image
 */
void renderPicture(Picture *img);

#endif
