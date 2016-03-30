 /**
 * \file animh
 * \brief Composant de l'interface graphique ustilisateur: la carte anim�e
 * \author Aubin Detrez
 */
#include "animCard.h"

static Card table[RANGEE][CPRANGEE]; // chaque carte de la table, 0 d�s la fin d'une rangee

static Card mvCard; // moving card

static Card newTable[RANGEE][CPRANGEE]; // chaque carte de la prochaine table, 0 d�s la fin d'une rangee

static int cardSet[2][10]; // les dix cartes choisient par les joueurs, tableau en 0 pour les cartes, tableau en [1] pour le rang�es on sont poss�ses les cartes

static int curseur; // indicatif dans cardSet de la carte manipul�e

static int rangee; // rangee manipul�e

static int emp; // emplacement manipul�

static SDL_Rect posPlayer[MAXJOUEUR]; // position de tout les joueurs

static bool justStarting; // viens juste de commancer une partie

static bool isMoving; // les animations sont en cours

//static Text hTexte; // texte pour le nombre de t�tes prisent par un joueur

static Uint32 timer;

int xi,yi,xf,yf; // position initiales et finales de la carte

bool isAnimating()
{
  return isMoving;
}


/**
 * \fn bool compareTable()
 * \brief comparer table et new table pour d�bug
 * affiche dans la terminable les diff�rences
 * \return true si les deux tableau sont identiques
 */
bool compareTable()
{
	int i,z;
	bool result=true;
	for(i=0;i<RANGEE;i++)
	{
		for(z=0;z<CPRANGEE;z++)
		{
			if(table[i][z].id!=newTable[i][z].id)
			{
				result=false;
				printf("\033[6m %3d/%3d \033[0m",table[i][z].id,newTable[i][z].id);
			}
			else
				printf("   ok  ");
		}
		printf("\n");
	}
	return result;
}


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
 * 0 si toutes les cartes on d�j� �taient retir�es
 */
 static int getMinCardSet()
 {
     int min=0,i;
     for(i=0;i<10;i++)
     {
         if(cardSet[0][i]>0 && (cardSet[0][min]<=0 || cardSet[0][i]<cardSet[0][min]))
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
     {
        cardSet[0][i]=0;
        cardSet[1][i]=0;
     }

 }
 /**
  * \fn static int finRg(int rg)
  * \param rg une rang�e de table
  * \return dernier indice de la rangee
  */
static int finRg(int rg)
{
    if(rg<0 || rg>=4)
        return -1;
    int i;
    for(i=0;i<CPRANGEE && table[rg][i].id>0;i++)
    {}
    if(i<=0)
    {
        printf("finRg: ERROR rang�e %d vide !!\n",rg);
        return 0;
    }
    if(table[rg][i-1].id<=0)
      printf("finRg: ERROR\n");
    return i-1;
}

 /**
  * \fn static int minDiffRangee(int id)
  * \brief indice dans table de la rang�e avec la dif�rence minimum avec la carte id
  * \param id carte � �valuer
  * \return la rang�e ou il y a la plus pette diff�rence, -1 sinon
  */
 static int minDiffRangee(int id)
 {
    int i;
    int mindiff = 200;
    int indice = -1;
    int buff;
    for(i=0;i<4;i++)
    {
        buff = finRg(i);
	printf("minDiffRangee: fin de la %d rangee: %dime colone\n",i,buff+1);
        if(table[i][buff].id>0 && table[i][buff].id < id && id - table[i][buff].id < mindiff)
        {
            mindiff = id - table[i][buff].id;
	    printf("minDiffRangee: dif�rence de %d trouv�e sur la %d rangee\n",mindiff,i);
            indice = i;
        }
    }
    if(mindiff>140)
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

     printf("prendMinHRg\n");
     for(i=0;i<4;i++)
    {
        somme=0;
        for(z=0;z<CPRANGEE && table[i][z].id>0;z++)
        {
            somme+=getNbBuffle(table[i][z].id);
        }
        if(somme<min)
        {
            min=somme;
            idMin = i;
        }
    }
    for(z=0;z<CPRANGEE && table[idMin][z].id>0;z++)
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
    for(z=0;z<CPRANGEE && table[rg][z].id>0;z++)
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
    for(i=0;i<CPRANGEE && table[rg][i].id>0;i++)
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
    if(cardSet[0][val]>0 && cardSet[0][val]<=104) // valide
    {
        mvCard.id = cardSet[0][val];
        curseur = val;
        xi = posPlayer[curseur].x;
        yi = posPlayer[curseur].y;
        rangee = minDiffRangee(mvCard.id);
        if(rangee<0)
    	{
            rangee = prendMinRg();
            emp=0; // carte au d�but de la rang�e
        }
        else if(nbCarteRg(rangee)>=CPRANGEE)
        {
	        printf("upMvCard: take rg %d\n",rangee+1);
            prendRg(rangee);
            emp=0;
        }
        else
	    {
	        printf("upMvCard: put at the end of the rg\n");
            emp = finRg(rangee)+1;
    	}

	    printf("upMvCard: card %d is going to be the %dieme card of the %d rg\n",mvCard.id,emp+1,rangee+1);
        xf = table[rangee][emp].rect.x;
        yf = table[rangee][emp].rect.y;
	    mvCard.rect.x=xi;
	    mvCard.rect.y=yi;
	    printf("upMvCard: going to %d/%d to %d/%d\n",xi,yi,xf,yf);
        timer = SDL_GetTicks();
        cardSet[0][curseur]=0;
    }
    else
    {
        printf("upMvCard: moving stopped because getMinCardSet returned %d\n",cardSet[0][val]);
        isMoving=false;
        compareTable();
    }
 }

 /**
  * \fn void afficherTable(Card **tab)
  * \brief affiche � l'�cran le tableau de carte tab
  * \param tab tableau � afficher
  */
  void afficherTable(Card tab[RANGEE][CPRANGEE])
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
  void positionnerTable(Card tab[RANGEE][CPRANGEE])
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

/**
 * \fn void positionnerJoueur(SDL_rect* tab)
 * \brief permet de positionner le tableau de joueur
 */
void positionnerJoueur(SDL_Rect* tab)
{
  int i;
  for(i=0; i<MAXJOUEUR; i++)
    {
        tab[i].x = POSJOUEUR_X;
        tab[i].y = POSJOUEUR_Y + i*(SIZEJOUEUR);
    }
}

void initAnimCard()
{
    initCard();
    resetTables();
    positionnerJoueur(posPlayer);
    positionnerTable(table);
    positionnerTable(newTable);
    justStarting = true;
    isMoving=false;
    mvCard.rect.w = CARD_W;
    mvCard.rect.h = CARD_H;

}

void updateAnimCard(DataGame* data)
{
    int i,z;
    if(justStarting)
    {
        justStarting = false;
        isMoving = false;
        for(i=0;i<4;i++) // newTable <- data.table
            for(z=0;z<CPRANGEE;z++)
                newTable[i][z].id=data->table[i][z];
        resetCardSet();
    }
    else if(!isMoving) // pas de mouvement en cour
    {
        sauvTable();
        for(i=0;i<4;i++) // newTable <- data.table
            for(z=0;z<CPRANGEE;z++)
                newTable[i][z].id=data->table[i][z];
        for(i=0;i<10;i++) // cardSet <- data.tour
    	{
            cardSet[0][i] = data->turn[i];
            cardSet[1][i] = data->place[i]; // rang�e o� doit �tre pos�e la carte
	        printf("%d -> %dieme rangee\n",cardSet[0][i],cardSet[1][i]+1);
	    }
	printf("\n");
        isMoving = true;
        upMvCard();
    }
    else
        printf("updateAnimCard: ERROR animation is running and new data is coming\n");

}

void renderAnimCard()
{
  int deltaT;
  float val;
    if(isMoving) // on commence pas, elle bouge
    {
      if(mvCard.rect.x<xf) // animation termin�e
      {
    	printf("renderAnimCard: card %d arrived at x=%d xf=%d\n",mvCard.id,mvCard.rect.x,xf);
    	table[rangee][emp].id=mvCard.id; // on pose la carte
    	upMvCard(); // on passe � l'animation suivante
    	printf("renderAnimCard: switch mv card, card %d isMoving \n",mvCard.id);
      }
      else // on fait bouger la carte
      {
    	deltaT = SDL_GetTicks()-timer;
        val = -2*K*deltaT/VITESSE + K;
    	//tripleT = deltaT*deltaT*deltaT;
	    mvCard.rect.x = xi + (xf-xi)*(deltaT/(float)VITESSE);
    	mvCard.rect.y = ((yi-yf)/(2*K*K*K))*val*val*val + (yi+yf)/2;
	    /*mvCard.rect.x = xi + (xf-xi)*((tripleT)/(float)VITESSE);
    	mvCard.rect.y = yi + (yf-yi)*((tripleT)/(float)VITESSE);*/
      }
        afficherTable(table);
         renderCard(&mvCard);
    }
    else // on a terminer de bouger
    {
      afficherTable(newTable);// on affiche la table termin�e
    }
}

void destroyAnimCard()
{
    detroyCard();
}
