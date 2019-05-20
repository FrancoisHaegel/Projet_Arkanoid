#include "collision.h"
#include <math.h>
#include "gameManager.h"


void colliding() {
    if (ceil(((ball.y) / 16) < 20)) {
        int col = (int) ((ball.x) / 32);
        int row = (int) (((ball.y) / 16));
        //check if a brick is at this location
        if(col > -1 && col < 13 && row > -1 && row < 20)
        if (brick_list[col][row].bc != TRANSPARENT) {
            resolveCollision(&brick_list[col][row]);
        }
    }
}

void resolveCollision(BRICK *brick) {
    ball.vy = ball.vy * (-1);
    brick->bc = TRANSPARENT;
    brickCount--;
    if(brickCount == 0 && currentLevel != nbLevel + 1){
        nextLevel();
    }
}
