#include "ball.h"

/*
void init_ball(void){
    ball.x = win_surf->w / 2;
	ball.y = win_surf->h / 2;
	ball.vx = 6.0;
	ball.vy = 10.0;
	ball.rayon = 20;
}
 */

void init_ball(int x, int y) {
    ball.x = x;
    ball.y = y;
    //ball.vx = 6.0;
    //ball.vy = 10.0;
    ball.vx = 0.0;
    ball.vy = 0.0;
    ball.rayon = 10;
}