// libs
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// headers
#include "utils.h"
#include "draw.h"
#include "print.h"
#include "ball.h"

// local variables
Uint64 prev, now; // timers
double delta_t;  // durée frame en ms
int x_vault;
int score = 0;

void init()
{
	init_draw();
	init_print();
	init_ball();
}

// fonction qui met à jour la surface de la fenetre "win_surf"
void draw()
{
	print_background();
	print_score(score);
	print_ball();
	
	// deplacement
	ball.x += (ball.vx / delta_t);
	ball.y += (ball.vy / delta_t);

	// collision pad
	if (ball.y > win_surf->h - srcVaiss.h - ball.rayon && ball.y < win_surf->h - srcVaiss.h){
		if(ball.x > x_vault && ball.x < x_vault + srcVaiss.w){

			if(ball.vy > 0)
				ball.vy *= -1;

			// renvoie dans la direction du côté du pad qui à été touché
			if(((x_vault + srcVaiss.w/2) - ball.x) > 0)
				if (ball.vx > 0)
					ball.vx *= - 1;
			else
				if (ball.vx < 0)
					ball.vx *= - 1;

		}
	}

	// collision bord
	if ((ball.x < 1) || (ball.x > (win_surf->w - ball.rayon)))
		ball.vx *= -1;
	if ((ball.y < 1) || (ball.y > (win_surf->h - ball.rayon)))
		ball.vy *= -1;

	// touche bas -> rouge
	if (ball.y >(win_surf->h - ball.rayon))
		srcBall.y = 64;

	// touche haut -> vert
	if (ball.y < 1)
		srcBall.y = 96;

	// vaisseau
	dest.x = x_vault;
	dest.y = win_surf->h - 32;

	print_vaisseau();
}

int main(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0 )
			return 1;

	init();
    
	bool quit = false;
	while (!quit)
	{
		SDL_Event event;
		while (!quit && SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					// touche clavier
					case SDLK_LEFT:  x_vault -= 10; break;
					case SDLK_RIGHT: x_vault +=10; break;
					case SDLK_ESCAPE: quit = true; break;
					default: break;
				}
				break;
			// pad x is set to mouse x minus half of pads width
			case SDL_MOUSEMOTION: x_vault = event.motion.x - (srcVaiss.w/2);	break;
			case SDL_MOUSEBUTTONDOWN:
				printf("mouse click %d\n", event.button.button);
				break;
			default: break;
			}
		}
		prev = now;
		now = SDL_GetPerformanceCounter();
		delta_t = (double)((now - prev) * 1000 / (double)SDL_GetPerformanceFrequency());
		draw();
		SDL_UpdateWindowSurface(pWindow); 
	}
    SDL_Quit();
    return 0;
}
