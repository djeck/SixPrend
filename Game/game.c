#include "game.h"

void eventGame()
{
  SDL_Event event;
	while (SDL_PollEvent(&event))
	{
	  if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT )
	  {
	    if(collisionWithMouse(choixQuit.rect,event.button.x,event.button.y))
	    {
	      changeStep(end);
	    }
	    if(collisionWithMouse(choixBack.rect,event.button.x,event.button.y))
	    {
	      changeStep(menu);
	    }
	      
	  }
	  else if( event.type == SDL_MOUSEMOTION )
	  {
	      choixQuit.select=collisionWithMouse(choixQuit.rect,event.motion.x,event.motion.y);
	      choixBack.select=collisionWithMouse(choixBack.rect,event.motion.x,event.motion.y);
	  }
		switch(event.type)
		{
			case SDL_QUIT:
				changeStep(end);
			break;
		}
	}
}

