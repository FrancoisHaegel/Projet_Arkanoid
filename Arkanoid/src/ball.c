#include "ball.h"

void init_ball(int x, int y) {
    ball.x = x;
    ball.y = y;
    ball.vx = 0.0;
    ball.vy = 0.0;
    ball.rayon = 10;
}