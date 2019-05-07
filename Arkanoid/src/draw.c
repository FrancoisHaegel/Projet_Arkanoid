#include "draw.h"

SDL_Window* pWindow = NULL;
SDL_Surface* win_surf = NULL;

void init_draw(void){
    pWindow = SDL_CreateWindow("Arkanoid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 428, 600, SDL_WINDOW_SHOWN);
	win_surf = SDL_GetWindowSurface(pWindow);
}

void drawAt(SDL_Surface* src, const SDL_Rect* srcrect, SDL_Rect* dstrect){
    SDL_BlitSurface(src, srcrect, win_surf, dstrect);
}