//
// Created by nantoni on 07/05/19.
//

#include "gameManager.h"

void win(){
    play = false;
}

void loose(){
    play = false;
}

void addLive(){
    if(nbLives < 5){
        nbLives++;
    }
}

void removeLive(){
    nbLives--;
    if(nbLives == 0){
        loose();
    }
}

void addScore(int point){
    score += point;
}