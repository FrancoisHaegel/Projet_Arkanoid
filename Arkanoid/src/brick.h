#ifndef BRICK_H
#define BRICK_H

#include <stdio.h>
#include <stdlib.h>

#include "draw.h"

typedef enum
{
    TRANSPARENT = 10,
    BLANC = 0,
    ORANGE = 1,
    BLEU_CLAIR = 2,
    VERT = 3,
    ROUGE = 4,
    BLEU = 5,
    ROSE = 6,
    JAUNE = 7,
    GRIS = 8,
    OR = 9,
} Brick_color;

typedef struct { int x; int y; Brick_color bc; unsigned int level; unsigned int spriteCount; } BRICK;

// List of all bricks
BRICK** brick_list;

int row_nbr;
int column_nbr;

// Load and display the bricks from a txt file
void load_brick_from_file(const char* path);

#endif // !BRICK_H
 