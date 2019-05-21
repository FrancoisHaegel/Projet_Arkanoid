//
// Created by nantoni on 07/05/19.
//

#ifndef ARKANOID_GAMEMANAGER_H
#define ARKANOID_GAMEMANAGER_H

// libs
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// headers
#include "utils.h"
#include "draw.h"
#include "print.h"
#include "ball.h"
#include "brick.h"
#include "collision.h"


int x_vault;
bool play;
bool gameStarted;

unsigned int nbLevel;
unsigned int currentLevel;
unsigned int brickCount;
unsigned int score;
unsigned int nbLives;

// local variables
Uint64 prev, now; // timers
double delta_t;  // durée frame en ms


// fonction qui met à jour la surface de la fenetre "win_surf"
void draw();


void init();
bool start();
void nextLevel();
void win();
void loose();
void addLive();
void removeLive();
void addScore(int point);



#endif //ARKANOID_GAMEMANAGER_H
