#ifndef COLLISION_H
#define COLLISION_H

#include <stdbool.h>

#include "ball.h"
#include "brick.h"

// functions
void colliding();
void resolveCollision(BRICK * brick);

#endif // !COLLISION_H
