 /**
 * \file animh
 * \brief Composant de l'interface graphique ustilisateur: la carte anim�e
 * \author Aubin Detrez
 */
#include "animCard.h"

static Card table[RANGEE][CPRANGEE]; // chaque carte de la table, 0 d�s la fin d'une rangee

static Card mvCard; // moving card

static Card newTable[RANGEE][CPRANGEE]; // chaque carte de la prochaine table, 0 d�s la fin d'une rangee

static int cardSet[10]; // les dix cartes choisient par les joueurs

static int curseur; // indicatif dans cardSet de la carte manipul�e

static int rangee; // rangee manipul�e

static int emp; // emplacement manipul�

static SDL_Rect posPlayer[MAXJOUEUR]; // position de tout les joueurs

static bool justStarting; // viens juste de commancer une partie

static bool isMoving; // les animations sont en cours

static Text hTexte; // texte pour le nombre de t�tes prisent par un joueur

static Uint32 timer;

int xi,yi,xf,yf; // position initiales et finales de la carte

/**
 * \fn int getNbBuffle(int cardId)
 * \brief retourne le nombre de t�te d'une carte
 * \param cardId le num�ro sur la carte
 * \return le nombre de carte
 */
int getNbBuffle(int cardId)
{
  if(cardId<=0 || cardId>104)
  {
    printf("getNbBuffle: ERROR no card with number \n");
    return 0;
  }
  else if(cardId==55)
    return 7;
  else if(cardId%11==0)
    return 5;
  else if(cardId%10==0)
    return 3;
  else if(cardId%5==0)
    return 2;
  else
    return 1;

}
/**
 * \fn static void sauvTable()
 * \brief suavegarde le tableau newTable dans table
 * newTable est initialis� � z�ro
 */
static void sauvTable()
{
    int i,z;
    for(i=0;i<RANGEE;i++)
        for(z=0;z<CPRANGEE;z++)
        {
            table[i][z].id=newTable[i][z].id;
            newTable[i][z].id=0;
        }
}

/**
 * \fn static void resetTables()
 * \brief remplace le contenu de table et newTable par des 0
 */
static void resetTables()
{
    int i,z;
    for(i=0;i<RANGEE;i++)
        for(z=0;z<CPRANGEE;z++)
        {
            table[i][z].id=0;
            newTable[i][z].id=0;
        }
}

/**
 * \fn static int getMinCardSet()
 * \brief prend la carte la plus petite dans cardSet
 * note: il faudra mettre la valeure de la carte � 0 dans cardSet une fois plac�e
 * \return identifiant dans cardSet de la carte chosit (correspond aussi au joueur dans posPlayer) ************ v�rifier **************
 */
 static int getMinCardSet()
 {
     int min=0,i;
     for(i=0;i<10 && cardSet[i]>0;i++)
     {
         if(cardSet[i]<cardSet[min])
            min=i;
     }
     return min;
 }

 /**
  * \fn static void resetCardSet()
  * \brief met � zero les valeures de cardSet
  */
 static void resetCardSet()
 {
     int i;
     for(i=0;i<10;i++)
        cardSet[i]=0;

 }
 /**
  * \fn static int finRg(int rg)
  * \param rg une rang�e de table
  * \return dernier �l�ment de la rang�e, -1 ou 0 si prob�me
  */
static int finRg(int rg)
{
    if(rg<0 || rg>=4)
        return -1;
    int i;
    for(i=0;i<6 && table[rg][i].id>0;i++)
    {}
    if(i<=0)
    {
        printf("finRg: ERROR rang�e %d vide !!\n",rg);
        return 0;
    }
    return table[rg][i-1].id;
}

 /**
  * \fn static int minDiffRangee(int id)
  * \brief indice dans table de la rang�e avec la dif�rence minimum avec la carte id
  * \param id carte � �valuer
  * \return la rang�e ou il y a la plus pette diff�rence, -1 sinon
  */
 static int minDiffRangee(int id)
 {
     int mindiff = 200;
     int indice,i;
     int buff;
    for(i=0;i<4;i++)
    {
        buff = finRg(i);
        if(buff>0 && table[i][buff].id < id && id - table[i][buff].id < mindiff)
        {
            mindiff = id - table[i][buff].id;
            indice = buff;
        }
    }
    if(mindiff>103)
        return -1;
    return indice;
 }

 /**
  * \fn static int prendMinRg()
  * \brief le on supprime la rangee avec le minimum de t�te
  * \return l'indice dans table pour y poser la carte
  */
 static int prendMinRg()
 {
     int i,z;
     int idMin=0,min=550,somme;
     for(i=0;i<4;i++)
    {
        somme=0;
        for(z=0;z<6 && table[i][z].id>0;z++)
        {
            somme+=getNbBuffle(table[i][z].id);
        }
        if(somme<min)
        {
            min=somme;
            idMin = i;
        }
    }
    for(z=0;z<6 && table[idMin][z].id>0;z++)
    {
        table[idMin][z].id = 0;
    }
    return idMin;

 }
 /**
  * \fn static int prendRg(int rg)
  * \brief on supprime la rangee
  * \return l'indice dans table pour y poser la carte
  */
 static int prendRg(int rg)
 {
     int z;
     if(rg<0 || rg>=4)
     {
         printf("prendRg: ERROR\n");
         return -1;
     }
    for(z=0;z<6 && table[rg][z].id>0;z++)
    {
        table[rg][z].id = 0;
    }
    return rg;

 }

 /**
  * \fn static int nbCarteRg(int rg)
  * \param rg rang�e
  * \return nombre de carte sur la rang�e
  */
 static int nbCarteRg(int rg)
 {
    int i;
    for(i=0;i<6 && table[rg][i].id>0;i++)
    {}
    return i;
 }

 /**
  * \fn static void upMvCard()
  * \brief met � jour les donn�es de la carte en mouvement
  */
 static void upMvCard()
 {
    int val = getMinCardSet();
    if(cardSet[val]>0 && cardSet[val<=104]) // valide
    {
        mvCard.id = cardSet[val];
        curseur = val;
        xi = posPlayer[curseur].x;
        yi = posPlayer[curseur].y;
        rangee = minDiffRangee(mvCard.id);
        if(rangee<0)
        {
            rangee = prendMinRg();
            emp=0; // carte au d�but de la rang�e
        }
        else if(nbCarteRg(rangee)>=6)
        {
            prendRg(rangee);
            emp=0;
        }
        else
            emp = finRg(rangee);
        xf = table[rangee][emp].rect.x;
        yf = table[rangee][emp].rect.y;
        timer = SDL_GetTicks();
        cardSet[curseur]=0;
    }
    else
        isMoving=false;
 }

 /**
  * \fn void afficherTable(Card **tab)
  * \brief affiche � l'�cran le tableau de carte tab
  * \param tab tableau � afficher
  */
  void afficherTable(Card **tab)
  {
      int i,z;
      for(i=0; i<RANGEE; i++)
        for(z=0; z<CPRANGEE && tab[i][z].id>0 && tab[i][z].id<=104; z++)
            renderCard(&tab[i][z]);
  }
/**
 * \fn void positionnerTable(Card** tab)
 * \brief initialise la position � l'�cran des cartes
 */
  void positionnerTable(Card** tab)
  {
      int i,z;
      for(i=0; i<RANGEE; i++) // on calcule les positions des cartes de la tables
        for(z=0; z<CPRANGEE; z++)
        {
            /*
             * i : rangee [0;3]
             * z : cartes de chaque rang�e [0;5]
             */
            tab[i][z].rect.x = POSTABLE_X + z*(CARD_W + DECHAND); // l'ecart entre les cartes est le m�me que pour la main
            tab[i][z].rect.y = POSTABLE_Y + i*(CARD_H + DECRANGEE);
            tab[i][z].rect.w = CARD_W;
            tab[i][z].rect.h = CARD_H;
            tab[i][z].id=0;
            tab[i][z].selected=false;
        }
  }

void initAnimCard()
{
    initCard();
    resetTables();
    positionnerTable(table);
    positionnerTable(newTable);
    justStarting = true;
    isMoving=false;

}

void updateAnimCard(DataGame* data)
{
    int i,z;
    if(justStarting)
    {
        justStarting = false;
        isMoving = false;
        for(i=0;i<4;i++) // newTable <- data.table
            for(z=0;z<6;z++)
                newTable[i][z].id=data->table[i][z];
        resetCardSet();
    }
    else if(!isMoving) // pas de mouvement en cour
    {
        sauvTable();
        for(i=0;i<4;i++) // newTable <- data.table
            for(z=0;z<6;z++)
                newTable[i][z].id=data->table[i][z];
        for(i=0;i<10;i++) // cardSet <- data.tour
            cardSet[i] = data->turn[i];
        isMoving = true;
        upMvCard();
    }
    else
        printf("updateAnimCard: ERROR animation is running and new data is coming\n");

}

void renderAnimCard()
{
    if(justStarting) // on commence
    {
        afficherTable(newTable);
    }
    else if(isMoving) // on commence pas, elle bouge
    {
        afficherTable(table);
    }
    else
    {

    }
}

void destroyAnimCard()
{
    //destroyCard();
}
