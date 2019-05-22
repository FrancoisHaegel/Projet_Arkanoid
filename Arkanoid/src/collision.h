#ifndef COLLISION_H
#define COLLISION_H

#include <stdbool.h>

#include "ball.h"
#include "brick.h"
#include "bonus.h"
#include "draw.h"

// functions
void colliding(double delta_t);
void resolveCollision(BRICK * brick, double delta_t);
void destroyBrick(BRICK *brick);
void collisionBonus(int x_vault, int w_vault);


#endif // !COLLISION_H
