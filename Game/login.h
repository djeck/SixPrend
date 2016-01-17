#ifndef LOGIN_H
#define LOGIN_H

#define BACKGROUNDPATH "../media/background.bmp"
#define FONTPATH "../media/DK Prince Frog.otf"
#define FONTSIZE 256

#include <SDL2/SDL_ttf.h>
#include "inc.h"

void eventLogin();
void initLoginRender();
void renderLogin();
void freeLoginRender();

#endif
