//
// Created by nantoni on 21/05/19.
//

#ifndef ARKANOID_BONUS_H
#define ARKANOID_BONUS_H


typedef enum
{
    S = 0,
    C = 1,
    L = 2,
    E = 3,
    D = 4,
    B = 5,
    P = 6,
} Bonus_type;

typedef struct { unsigned int x; unsigned int y; Bonus_type bt; unsigned int spriteCount; } BONUS;

// List of bonus to display
BONUS* bonus_list;

// Number of currently printed bonus (6 max)
unsigned int bonus_number;

void init_bonus();

#endif //ARKANOID_BONUS_H
