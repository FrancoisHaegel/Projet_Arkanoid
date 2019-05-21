#ifndef COLLISION_H
#define COLLISION_H

#include <stdbool.h>

#include "ball.h"
#include "brick.h"

// functions
void colliding(double delta_t);
void resolveCollision(BRICK * brick, double delta_t);

#endif // !COLLISION_H
