#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct { double x; double y;  double vx; double vy; double rayon;} ball;

Uint64 prev, now; // timers
double delta_t;  // durée frame en ms
int x_vault;
int score = 0;

SDL_Window* pWindow = NULL;
SDL_Surface* win_surf = NULL;
SDL_Surface* plancheSprites = NULL;
SDL_Surface* plancheASCIISprites = NULL;

SDL_Rect srcBg = { 0,128, 96,128 }; // x,y, w,h (0,0) en haut a gauche
SDL_Rect srcBall = { 0,96,24,24 };
SDL_Rect scrVaiss = { 128,0,128,32 };

void print_ascii(char c, int x, int y){
	SDL_Rect src = { 0, 0, 14,20 }; // x,y, w,h (0,0) en haut a gauche
	switch (c)
	{
		case '0':
			src.x = 2;
			src.y = 38;
			break;
		case '1':
			src.x = 34;
			src.y = 38;
			break;
		case '2':
			src.x = 66;
			src.y = 38;
			break;
		case '3':
			src.x = 98;
			src.y = 38;
			break;
		case '4':
			src.x = 130;
			src.y = 38;
			break;
		case '5':
			src.x = 163;
			src.y = 38;
			break;
		case '6':
			src.x = 194;
			src.y = 38;
			break;
		case '7':
			src.x = 226;
			src.y = 38;
			break;
		case '8':
			src.x = 258;
			src.y = 38;
			break;
		case '9':
			src.x = 290;
			src.y = 38;
			break;
	}

	SDL_Rect destASCII = { x,y,0,0 };
	SDL_BlitSurface(plancheASCIISprites, &src, win_surf, &destASCII);
}
char * toArray(int number)
{
	char * ns = (char*)malloc(5 * sizeof(char));
	sprintf(ns,"%05d",number);
	return ns;
}

void print_score(int score){
	char * arr_score = toArray(score);
	for(size_t i = 0; i < 5; i++){
		print_ascii(arr_score[i], i * 18 + 20, 20);
	}
}

void init()
{
	pWindow = SDL_CreateWindow("Arknoid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 600, SDL_WINDOW_SHOWN);
	win_surf = SDL_GetWindowSurface(pWindow);
	plancheSprites = SDL_LoadBMP("./sprites.bmp");
	plancheASCIISprites = SDL_LoadBMP("./Arkanoid_ascii.bmp");
	SDL_SetColorKey(plancheSprites, true, 0);  // 0: 00/00/00 noir -> transparent
	SDL_SetColorKey(plancheASCIISprites, true, 0);  // 0: 00/00/00 noir -> transparent

	ball.x = win_surf->w / 2;
	ball.y = win_surf->h / 2;
	ball.vx = 6.0;
	ball.vy = 10.0;
	ball.rayon = 21;
}


// fonction qui met à jour la surface de la fenetre "win_surf"
void draw()
{
	// remplit le fond 
	SDL_Rect dest = { 0,0,0,0 };
	for (int j = 0; j < win_surf->h; j+=128)
		for (int i = 0; i < win_surf->w; i += 96)
		{
			dest.x = i;
			dest.y = j;
			SDL_BlitSurface(plancheSprites, &srcBg, win_surf, &dest);
		}

	// print_score();
	// print_ascii('0', 17, 20);
	// print_ascii('0', 34, 20);
	// print_ascii('0', 51, 20);
	// print_ascii('0', 68, 20);

	print_score(score);
	
	// affiche balle
	SDL_Rect dstBall = {ball.x, ball.y, 0, 0};
	SDL_BlitSurface(plancheSprites, &srcBall, win_surf, &dstBall);


	// deplacement
	ball.x += (ball.vx / delta_t);
	ball.y += (ball.vy / delta_t);

	// collision pad
	if (ball.y > win_surf->h - scrVaiss.h - ball.rayon && ball.y < win_surf->h - scrVaiss.h){
		if(ball.x > x_vault && ball.x < x_vault + scrVaiss.w){
			printf("\a\n");

			score++;

			if(ball.vy > 0){
				ball.vy *= -1;
			}

			// renvoie dans la direction du côté du pad qui à été touché
			if(((x_vault + scrVaiss.w/2) - ball.x) > 0){
				if (ball.vx > 0){
					ball.vx *= - 1;
				}
			}else{
				if (ball.vx < 0){
					ball.vx *= - 1;
				}			
			}
		}
	}

	// collision bord
	if ((ball.x < 1) || (ball.x > (win_surf->w - ball.rayon)))
		ball.vx *= -1;
	if ((ball.y < 1) || (ball.y > (win_surf->h - ball.rayon)))
		ball.vy *= -1;

	// touche bas -> rouge
	if (ball.y >(win_surf->h - ball.rayon)){
		// ball.vy = 0;
		// ball.vx = 0;		
		srcBall.y = 64;
	}
	// touche haut -> vert
	if (ball.y < 1){
		srcBall.y = 96;
	}

	// vaisseau
	dest.x = x_vault;
	dest.y = win_surf->h - 32;
	SDL_BlitSurface(plancheSprites, &scrVaiss, win_surf, &dest);
}



int main(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
		return 1;
    }

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
			case SDL_MOUSEMOTION: x_vault = event.motion.x - (scrVaiss.w/2);	break;
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
