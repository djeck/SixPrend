/**
 * \file chatBox.h
 * \brief élément de l'interface graphique utilisateur: le chat
 * \author Aubin Detrez
 */
#ifndef CHATBOX_H
#define CHATBOX_H

#include "text.h"
#include "textBox.h"

#define NB_MSG 6
#define DY 30 // espace entre chaque rangée
#define CHAT_W 300

/**
 * \struct ChatBox
 * \brief regroupement de composants graphiques pour faire un chat
 */
typedef struct
{
  SDL_Rect rect; /*!< position et dimension pour l'enssemble des composants */
  Text messages[NB_MSG]; /*!< lignes, un par message*/
  char text[NB_MSG][100]; /*!< chaine de caractères, correspondant au contenu de messages */
  TextBox input; /*!< entrée de l'utilisateur */
  void (*callback)(char*); /*!< optionel (appelé lors de la saisie d'un message par l'utilisateur) */
  bool update; /*!< true si avant rendu on doit mettre à jour message avec text */
} ChatBox;

/**
 * \fn ChatBox createChatBox(int x,int y)
 * \brief initialisation des resources de chaque composantes et parametrage
 * \param x position selon x de l'enssemble
 * \param y position selon y de l'enssemble
 * \return objet chat
 */
ChatBox createChatBox(int x,int y);
/**
 * \fn void pushChatBox(ChatBox* ptr)
 * \brief ajouter un message au chat
 * le message en question est dans input.text, tout les messages précédent
 * vont être déssiné plus haut
 * \param ptr pointeur sur le chat
 */
void pushChatBox(ChatBox* ptr);
/**
 * \fn void inputChatBox(ChatBox* ptr,SDL_Event *event)
 * \brief gestion des évenements (entrées)
 * \param ptr pointeur vers le chat
 * \param event évenement à traiter
 */
void inputChatBox(ChatBox* ptr,SDL_Event *event);
/**
 * \fn void freeChatBox(ChatBox *img)
 * \brief libération des ressources graphiques associées au chat
 * \param img pointeur vers le chat
 */
void freeChatBox(ChatBox *img);
/**
 * \fn void renderChatBox(ChatBox *img)
 * \brief affichage à l'écran du chat
 * \param img pointeur vers le chat
 */
void renderChatBox(ChatBox *img);

#endif
