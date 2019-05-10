//
// Created by nantoni on 07/05/19.
//

#ifndef ARKANOID_GAMEMANAGER_H
#define ARKANOID_GAMEMANAGER_H

#include <stdbool.h>

unsigned int nbLevel;
unsigned int currentLevel;
unsigned int brickCount;

unsigned int score;
unsigned int nbLives;
bool play;

void win();
void loose();
void addLive();
void removeLive();
void addScore(int point);

#endif //ARKANOID_GAMEMANAGER_H
