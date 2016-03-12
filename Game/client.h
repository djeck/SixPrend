/**
 * \file client.h
 * \brief réseau
 * \author Aubin Detrez
 * 
 * Permet de ce connecter au serveur de jeu, lancer un thread
 * d'écoute et recevoir les données du serveur pas l'intermédiaire de callback
 *
 */
#ifndef CLIENT_H
#define CLIENT_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL_net.h>
#include <SDL2/SDL_thread.h>
#include <SDL2/SDL_timer.h>
#include "network.h"
#define PORT 2000 // port par défault utiliser par le serveur


/** 
 * \fn void initialisationReseau(char *strip,void (*backData)(Data*),void (*backList)(DataList*),void (*backGame)(DataGame*))
 * \brief initialisation du réseau
 * initialise la connection avec le serveur
 * \param strip chaine de caractère correspondant à l'ip du serveur (ex: "127.0.0.1")
 * \param backData callback pour la réception de données de type Data
 * \param backList callback pour la réception de données de type DataList
 * \param backGame callback pour la réception de données de type DataGame
 */
void initialisationReseau(char *strip,void (*backData)(Data*),void (*backList)(DataList*),void (*backGame)(DataGame*));
/** 
 * \fn void updateCallback(void (*backData)(Data*),void (*backList)(DataList*),void (*backGame)(DataGame*))
 * \brief changement de callback
 * rediriger les retour du thread de récption vers de nouvelles fonctions
 *
 * \param backData callback pour la réception de données de type Data
 * \param backList callback pour la réception de données de type DataList
 * \param backGame callback pour la réception de données de type DataGame
 */
void updateCallback(void (*backData)(Data*),void (*backList)(DataList*),void (*backGame)(DataGame*));
/** 
 * \fn void freeRessourcesReseau()
 * \brief libération des ressources si elles sont initialisées
 *
 */
void freeRessourcesReseau();

/** 
 * \fn void reception()
 * \brief lancer la réception dans un nouveau thread
 * les données sont retournées par des callback définis dans initialisationReseau ou updateCallback
 */
void reception();

/** 
 * \fn void sendMsg(char *msg)
 * \brief transmettre le message au serveur
 * les messages sont afficher dans les chats des clients de la même salle (d'attente comme de jeu)
 * \param msg chaine de caractère à transmettre
 */
void sendMsg(char *msg);
/**
 * \fn void askList()
 * \brief demande au serveur de transmettre la liste des salles
 * non bloquante et la réponse du serveur sera transmise au callback associé à son type (par le thread de réception)
 */
void askList();
/** 
 * \fn void join(char* str,int passwd)
 * \brief demande à rejoindre une salle de jeu
 * réponce du serveur via callback
 * \param str chaine de caractère pour le nom de la salle
 * \param passwd mot de passe (-1 si non utilisé)
 */
void join(char* str,int passwd);
/**
 * \fn void sendQuit()
 * \brief demande au serveur à quitter proprement
 * lorsque le thread de réception recevra la réponce du serveur il se terminera
 */
void sendQuit();
/** 
 * \fn void create(char* str,int passwd)
 * \brief demande à creer une salle de jeu
 * réponce du serveur via callback
 * \param str chaine de caractère pour le nom de la salle
 * \param passwd mot de passe (-1 si non utilisé)
 */
void create(char* str,int passwd);
/** 
 * \fn void startGame()
 * \brief demande à commencer une partie
 * réponce du serveur via callback
 */
void startGame();
/** 
 * \fn void choice(int choice)
 * \brief envoie le choix du joueur au serveur
 * réponce du serveur via callback
 * \param le noméro de la carte choisit ([1;104])
 */
void choice(int choice);

/** 
 * \fn int isNetInitialised()
 * \brief vérifier que le réseau est initialisé
 * \return 1 si initialisé, 0 sinon
 */
int isNetInitialised();

/** 
 * \fn void printData()
 * \brief afficher le contenu du buffer data(cf client.c) dans la console
 */
void printData();
/** 
 * \fn void setWait(bool arg0)
 * \brief fait attendre le thread client pour la réception d'une DataGame
 * \param true si peut réceptionner, false sinon
 */
void setWait(bool arg0);


#endif
