#include "menu.h"

void eventMenu()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_QUIT:
				printf("eventLogin: event quit received\n");
				changeStep(end);
			break;
			case SDL_KEYUP:
			break;
		}// fin du switch
	}
}