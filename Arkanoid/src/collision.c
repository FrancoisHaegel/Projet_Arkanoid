#include "collision.h"
#include <math.h>
#include "gameManager.h"

void colliding(double delta_t) {
    if (ceil(((ball.y) / 16) < 20)) {
        int col = (int) ((ball.x + ball.rayon) / 32);
        int row = (int) ((ball.y + ball.rayon) / 16);
        //check if a brick is at this location
        if(col > -1 && col < 13 && row > -1 && row < 20)
        if (brick_list[col][row].bc != TRANSPARENT) {
            resolveCollision(&brick_list[col][row], delta_t);
        }
    }
}

void resolveCollision(BRICK *brick, double delta_t) {
    double ballCenterX = ball.x + ball.rayon;
    double ballCenterY = ball.y + ball.rayon;

    ballCenterX -= (ball.vx / delta_t);
    ballCenterY -= (ball.vy / delta_t);

    double brickCenterX = brick->x + 16;
    double brickCenterY = brick->y + 8;

    ////////3e tentative /////////
    if(ballCenterY < brickCenterY - 8
        && ballCenterX > brickCenterX - 16
        && ballCenterX < brickCenterX + 16){
        ball.vy = ball.vy * (-1);
    }else if(ballCenterY > brickCenterY + 8
        && ballCenterX > brickCenterX - 16
        && ballCenterX < brickCenterX + 16){
        ball.vy = ball.vy * (-1);
    }else if(ballCenterX > brickCenterX - 16
      && ballCenterY > brickCenterY - 8
      && ballCenterY < brickCenterY + 8){
        ball.vx = ball.vx * (-1);
    }else if(ballCenterX > brickCenterX + 16
      && ballCenterY > brickCenterY - 8
      && ballCenterY < brickCenterY + 8){
        ball.vx = ball.vx * (-1);
    }

    bool break_brick = true;

    switch (brick->bc){
        case BLANC:
            addScore(50);
            break;
        case ORANGE:
            addScore(60);
            break;
        case BLEU_CLAIR:
            addScore(70);
            break;
        case VERT:
            addScore(80);
            break;
        case ROUGE:
            addScore(90);
            break;
        case BLEU:
            addScore(100);
            break;
        case ROSE:
            addScore(110);
            break;
        case JAUNE:
            addScore(120);
            break;
        case GRIS:
            if(brick->level > 1){
                glow(brick);
                break_brick = false;
                brick->level--;
                addScore(100 * currentLevel);
            }
            break;
    }

    if(break_brick){
        brick->bc = TRANSPARENT;
        brickCount--;
    }
    if(brickCount == 0 && currentLevel != nbLevel + 1){
        nextLevel();
    }
}
