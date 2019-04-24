#ifndef PRINT_H
#define PRINT_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#include "draw.h"
#include "utils.h"
#include "ball.h"
#include "brick.h"

#define ARKANOID_SPRITE_PATH "./res/Arkanoid_sprites.bmp"
#define OTHER_SPRITE_PATH "./res/sprites.bmp"
#define ASCII_SPRITE_PATH "./res/Arkanoid_ascii.bmp"

// global variables 
extern SDL_Surface* plancheSprites;
extern SDL_Surface* plancheASCIISprites;
extern SDL_Surface* plancheArkanoidSprites;

extern SDL_Rect srcBg; // x,y, w,h (0,0) en haut a gauche
extern SDL_Rect srcBall;
extern SDL_Rect srcVaiss;
extern SDL_Rect dest;

void init_print(void);
void print_ascii(const char c, const int x, const int y);
void print_score(const int score);
void print_background(void);
void print_ball(void);
void print_vaisseau(void);
void print_bricks(void);
SDL_Rect getBrickSprite(const Brick_color* bc);

#endif // !PRINT_H
 