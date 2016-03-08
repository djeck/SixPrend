#include "login.h"

/*
 * stoque le nom de l'utilisateur bien identifié
 * defini pour les etapes menu, mode, stat,game
 * ne pas utiliser sinon
 */
static char utilisateur[SIZESTR];

char* getUsername()
{
  return utilisateur;
}

static Etapes step; // étapes du login

static TextBox inputBox;
static Text imginstruction;
static Text lastTry;

void eventLogin()
{
    SDL_Event event;
    static char username[SIZESTR];
    static char password[SIZESTR];

    while (SDL_PollEvent(&event))
    {
      if(step == rLog)
	inputTextBox(&inputBox,&event);
      else
	inputPassBox(&inputBox,&event);
      
        switch(event.type)
        {
        case SDL_QUIT:
            printf("eventLogin: event quit received\n");
            changeStep(end);
            break;
        case SDL_KEYUP:
            if( event.key.keysym.scancode == SDL_SCANCODE_RETURN ||
                     event.key.keysym.sym == SDLK_TAB )
            {
                printf("eventLogin: input confirmed\n");
                if(step==rLog) // si l'utilisateur à validé la saisie du nom d'utilisateur, on recupère le résultat
                {
                    strcpy(username,inputBox.text); // on garde le nom d'utilisateur de côté
                    updateText(&imginstruction,"Password:");
                    inputBox.text[0]='\0';
                    updateTextBox(&inputBox);
                    step = rPass; // on lui demande le mot de passe
                }
                else if(step==rPass)// sinon si l'utilisateur valide le mot de passe saisie
                {
                    strcpy(password,inputBox.text);
                    int resultat = identifier(username,password);
		    inputBox.text[0]='\0'; // on efface le contenu
		    updateTextBox(&inputBox);
                    switch(resultat)
                    {
                    case 0: // mot de passe faux
                        printf("eventLogin: bad password\n");
                        updateText(&lastTry,"bad password");
                        updateText(&imginstruction,"Username:");
                        step=rLog; // il doit tout ressaisir
                        break;
                    case 1: // bien identifier
                        printf("eventLogin: successfully identified\n");
                        strcpy(utilisateur,username);
                        changeStep(menu);
                        break;
                    case 2: // nouveau compte
                        printf("eventLogin: new user registred\n");
                        strcpy(utilisateur,username);
                        changeStep(menu);
                        break;
                    default:
                        updateText(&lastTry,"error, keep trying");
                        printf("eventLogin: error, identifer(char*,char*) shouldnt return %d\n",resultat);
                        updateText(&imginstruction,"Username:");
                        step=rLog; // il doit tout ressaisir
                    }
                }
            }
            break;

        }
    }
}

extern SDL_Renderer* renderer;
static int renderinitialised = 0;

static Picture Background;


void initLoginRender()
{
    printf("initLoginRender: debut\n");

    Background = createPicture(BACKGROUNDPATH,0,0,1);


    imginstruction = createText("Username:",100,150,5);
    lastTry = createText(" ",100,50,5);
    inputBox = createTextBox("",100,200,5,true);

    step=rLog; // on va commencer par lui demander le nom d'utilisateur
    renderinitialised=1;
}


void renderLogin()
{
    if(renderinitialised==0)
        return;
    renderPicture(&Background);
    renderTextBox(&inputBox);
    renderText(&imginstruction);
    renderText(&lastTry);
}

void freeLoginRender()
{
    if(renderinitialised==0)
    {
        printf("freeLoginRender: ne peut pas liberer les ressources car elles n'ont pas etaient inititialisé\n");
        return;
    }

    renderinitialised=0; // pour etre sur que on ne dessine pas avec les ressources qui ne sont plus disponiblent
    freeTextBox(&inputBox);
    freePicture(&Background);
    freeText(&imginstruction);
    freeText(&lastTry);

    printf("freeLoginRender: liberation des ressources\n");
}

int identifier(char *username,char *password)
{
    FILE *fic;
    char loginlu[SIZESTR],passlu[SIZESTR];
    fic=fopen(FILELOGIN,"r+");
    if(fic==NULL)
    {
        printf("l'ouverture n'est pas bonne\n");
    }
    else
    {
        while(fscanf(fic,"%s %s",loginlu,passlu)==2) // tant qu'il y a des donnes valides à lire
        {
            if(strcmp(loginlu,username)==0) // le compte existe
            {
                if(strcmp(passlu,password)==0) // le mot de passe rentre est valide
                {
                    fclose(fic);
                    return 1;
                }
                else // mot de passe non valide
                {
                    fclose(fic);
                    return 0;
                }
            }
        }
        //fichier parcouru sans avoir pu trouver le compte: on le cree
        printf("login.c : identifier : AJOUT du joueur %s\n",username);
        fprintf(fic,"%s %s\n",username,password);
        fclose(fic);
        return 2;
    }
    return 0; // en cas d'erreur le mot de passe n'est pas validé
}

bool exist(char *username)
{
    FILE *fic;
    char usernmlu[SIZESTR];
    char passlu[SIZESTR];
    fic=fopen(FILELOGIN,"r+");
    if(fic==NULL)
    {
        printf("l'ouverture n'est pas bonne\n");
    }
    else
    {
        while(fscanf(fic,"%s %s",usernmlu, passlu)==2)
        {
            if(strcmp(usernmlu,username)==0)
            {
                return true;
            }
        }

    }
    printf("login.c : exist : le joueur n'existe pas\n");
    return false;
}

