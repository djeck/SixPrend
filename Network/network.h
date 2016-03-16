/**
 * \file network.h
 * \brief Fichier correspondant au structures et types de donnée pour le reseau
 * doit être le même sur le serveur et le client (note: sur le serveur c'est inc.hpp)
 * \author Aubin Detrez
 *
 */
#ifndef INC_HPP
#define INC_HPP

#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#define BUF_SIZE 100
#define BUF_LIST 640
#define MAXCONN 100

/* Les valeures possibles de [Data].car selon le [Data].dataType	*/

/* le serveur ne peut pas satisfaire la demande du client ou une erreur est constaté
	tab - indications suplémentaire */
#define CONN_ERROR 0

// le serveur ne peut plus acueillir de client
#define CONN_FULL 1

// le serveur demande à un client de se déconnecter
#define CONN_STOP 2

// connection est établie avec success
#define CONN_OK 3

// le client veut la liste des salles de jeu, le serveur renverra des DataList
#define CONN_LIST 4

/* le client veut rejoindre une salle
	tab - nom de la salle
	from - mot de passe de la salle ou -1
	les serveur répondra CONN/CONN_ERROR s'il y a un problème ou GAME_OK sinon
*/
#define CONN_JOIN 5

/* le client veut creer une salle de jeu
	tab - nom de la salle
	from - mot de passe ou -1 pour ne pas en utiliser
*/
#define CONN_CREATE 6

/*
 * le client est bien logger ou est bien etre dans la salle
 */
#define GAME_OK 7

// le client est demande à se logger
#define GAME_LOGIN 8

// erreur lors du login
#define GAME_ERROR 9

/*
 * le client demande à commance la partie ou le serveur
 * va transmettre les donnees pour un tour de table (de structure DataGame)
 */
#define GAME_START 10

/*
 * le serveur demande aux clients de choisir la carte, les clients lui envoie dans fom
 */
#define GAME_CHOICE 11

/*
 * le serveur declare fin du tour de table, le serveur va transmettre de nouvelles donnees DataGame
 */
#define END_TURN 12

/*
 * le server declare fin du jeu (un joueur est arrive à 66 points) le serveur attend un GAME_START pour repartir
 */
#define END_GAME 13

// changement de type de donnees, selon DataType
#define SWITCH 14

// quitter proprement
#define CONN_QUIT 15

/**	Les types de donnée	**/

/**
 * \enum DataType
 * \brief les types de paquet selon leurs fonction
 * correspond au champ dataType de la structure Data
 */
typedef enum {
    CONN=0, /*!< pour la connection*/
    MSG=1,  /*!< pour le chat (message)*/
    GAME=2  /*!< pour le jeu*/
} DataType;

/**
 * \struct Data
 * \brief données de base
 *  Données pour toute la partie connection
 */
typedef struct
{
    DataType dataType; /*!< type de donnée concerné*/
    char car;           /*!< information complementaire sur la nature des données*/
    char tab[BUF_SIZE]; /*!< buffer pour des chaines de caractére*/
    int32_t from;           /*!< source d'un message ou mot de passe pour rejoindre une salle*/
} __attribute__ ((packed)) Data;

/**
 * \struct DataList
 * \brief données spécifiques à la liste des salles
 * sont comme une liste chainée, dernier paquet contient end à true
*/
typedef struct
{
    char tab[BUF_LIST]; /*!< nom des salles espacé par '\n'*/
    _Bool end; /*!< true si le client n'a pas à attendre d'autre données de ce type*/
} __attribute__ ((packed)) DataList;

/**
 * \struct DataGame
 * \brief Données pour le jeu en lui même
 */
typedef struct
{
    int32_t table[4][6]; /*!< les cartes sur la table, 4 ranges de 10 cartes maximum, vaut 0 si derniere carte de la rangée */
    char users[10][BUF_SIZE]; /*!< nom de chaques joueurs */
    int32_t turn[10]; /*!< choix de chaque joueurs */
    int32_t scores[10]; /*!< scores de chaques joueur */
    int32_t hand[10]; /*!< main du joueur */
} __attribute__ ((packed)) DataGame;

#endif
