#ifndef BRICK_H
#define BRICK_H

#include "draw.h"

typedef enum
{
    BLANC = 0,
    ORANGE = 1,
    BLEU_CLAIR = 2,
    VERT = 3
} Brick_color;

typedef struct { int x; int y; Brick_color bc; } BRICK;

BRICK* brick_list;
int brick_number;

void load_brick_from_file(const char* path);

#endif // !BRICK_H
 