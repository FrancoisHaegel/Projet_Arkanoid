#ifndef COLLISION_H
#define COLLISION_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#include "ball.h"
#include "brick.h"

// functions
void colliding();
void resolveCollision(Brick brick)

#endif // !COLLISION_H
