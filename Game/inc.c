/*
 * Comprend les fonctions communes à tout le jeu
 */
#include "inc.h"

void changeStep(MainStep nextStep)
{
  if(nextStep==globalStep)
    return;
  switch(globalStep)
  {
    case login:
      	freeLoginRender(); // liberation des ressources du login
      break;
    case menu:
      //freeMenuRender();
      break;
    case mode:
      //freeModeRender();
      break;
    case stat:
      //freeStatRender();
      break;
    case game:
      //freeGameRender();
      break;
  }
  
  switch(nextStep)
  {
    case login:
      initLoginRender();
      break;
    case menu:
      //initMenuRender();
      break;
    case mode:
      //initModeRender();
      break;
    case stat:
      //initStatRender();
      break;
    case game:
      //initGameRender();
      break;
  }
  globalStep=nextStep;
}