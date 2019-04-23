#ifndef DRAW_H
#define DRAW_H

#include <SDL2/SDL.h>

// global variables 
extern SDL_Window* pWindow;
extern SDL_Surface* win_surf;

// functions
void init_draw(void);
void drawAt(SDL_Surface* src, const SDL_Rect* srcrect, SDL_Rect* dstrect);

#endif // !DRAW_H
 