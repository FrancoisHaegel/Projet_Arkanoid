#include "ball.h"

void init_ball(void){
    ball.x = win_surf->w / 2;
	ball.y = win_surf->h / 2;
	ball.vx = 6.0;
	ball.vy = 10.0;
	ball.rayon = 20;
}