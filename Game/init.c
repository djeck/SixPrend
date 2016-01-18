#include "init.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

SDL_Window * window;
SDL_Renderer * renderer;

void init()
{
	globalStep=none;
	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow("SixPrend",
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            WINDOW_WIDTH, WINDOW_HEIGHT,
			    0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if(window == NULL || renderer == NULL)
		exit(1);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	if(TTF_Init()==-1) {
	  printf("init:TTF_Init: %s\n", TTF_GetError());
	exit(2);
	}

}

void quit()
{

  TTF_Quit();
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  printf("quit: ressources bien liberer\n");
}
