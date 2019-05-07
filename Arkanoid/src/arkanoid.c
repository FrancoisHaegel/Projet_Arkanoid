// libs
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// headers
#include "gameManager.h"
#include "utils.h"
#include "draw.h"
#include "print.h"
#include "ball.h"
#include "brick.h"
#include "collision.h"

// local variables
Uint64 prev, now; // timers
double delta_t;  // durée frame en ms
int x_vault;
bool gameStarted = false;

void init() {
    play = true;
    score = 0;
    nbLives = 3;
    init_draw();
    init_print();
    init_ball(x_vault, win_surf->h - 56 - ball.rayon/2 );
    //init_ball(x_vault, win_surf->h - ball.rayon - 50);

    load_brick_from_file("./levels/lvl_1");
}

// fonction qui met à jour la surface de la fenetre "win_surf"
void draw() {
    print_background();
    print_bricks();
    print_ball();


    // deplacement
    ball.x += (ball.vx / delta_t);
    ball.y += (ball.vy / delta_t);

    // collision pad
    if (ball.y > win_surf->h - srcVaiss.h - ball.rayon/2 && ball.y < win_surf->h - srcVaiss.h) {
        if (ball.x > x_vault && ball.x < x_vault + srcVaiss.w) {

            if (ball.vy > 0)
                ball.vy *= -1;

            // renvoie dans la direction du côté du pad qui à été touché
            if (((x_vault + srcVaiss.w / 2) - ball.x) > 0) {
                if (ball.vx > 0)
                    ball.vx *= -1;
                else if (ball.vx < 0)
                    ball.vx *= -1;
            }
        }
    }

    // collision bord
    if ((ball.x < 1) || (ball.x > (win_surf->w - ball.rayon/2)))
        if(true){
            ball.vx *= -1;
        }
    if ((ball.y < 1) || (ball.y > (win_surf->h - ball.rayon/2)))
        ball.vy *= -1;

    // touche bas -> rouge
    if (ball.y > (win_surf->h - ball.rayon/2)) {
        srcBall.y = 64;
        //removeLive();
    }

    // touche haut -> vert
    if (ball.y < 1)
        srcBall.y = 96;

    // vaisseau
    dest.x = x_vault;
    dest.y = win_surf->h - 32;

    if (!gameStarted) {
        ball.x = x_vault + srcVaiss.w / 2 - ball.rayon / 2;
    }

    print_vaisseau();
    print_lives();
    print_score(score);
}

int main(int argc, char **argv) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        return 1;

    init();

    bool quit = false;
    while (!quit) {
        SDL_Event event;
        while (!quit && SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        // touche clavier
                        case SDLK_LEFT:
                            x_vault -= 10;
                            break;
                        case SDLK_RIGHT:
                            x_vault += 10;
                            break;
                        case SDLK_ESCAPE:
                            quit = true;
                            break;
                        default:
                            break;
                    }
                    break;
                    // pad x is set to mouse x minus half of pads width
                case SDL_MOUSEMOTION:
                    x_vault = event.motion.x - (srcVaiss.w / 2);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (!gameStarted) {
                        srcBall.y = 96;
                        gameStarted = true;
                        ball.vx = 6.0;
                        ball.vy = 10.0;
                    }
                    break;
                default:
                    break;
            }
        }
        prev = now;
        now = SDL_GetPerformanceCounter();
        delta_t = (double) ((now - prev) * 1000 / (double) SDL_GetPerformanceFrequency());
        if (play) {
            draw();
            colliding();
        }
        SDL_UpdateWindowSurface(pWindow);
    }
    SDL_Quit();
    return 0;
}
