//
// Created by nantoni on 07/05/19.
//

#include "gameManager.h"

void init() {
    gameStarted = false;
    play = true;
    score = 0;
    nbLives = 3;
    nbLevel = 3;
    currentLevel = 0;
    init_draw();
    init_print();
    init_ball(x_vault + ball.rayon, win_surf->h - 69 - ball.rayon);
    nextLevel();
}

bool start(){
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
                        case SDLK_RETURN:
                            if(!play)
                                restart();
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
                        ball.vy = -10.0;

                        //ball.vx = 12.0;
                        //ball.vy = -20.0;
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
    return  0;
}

void nextLevel(){
    currentLevel++;
    if(currentLevel > nbLevel)
        win();
    else{
        char str[2];
        sprintf(str, "%d", currentLevel);
        char a[14] = "./levels/lvl_";
        strcat(a, str);
        load_brick_from_file( a );
    }
}

void restart(){
    score = 0;
    nbLives = 3;
    currentLevel = 0;
    nextLevel();
    play = true;
}

void win(){
    play = false;
    print_text("CONGRATULATION", 14, 69, 400);
    print_text("RETURN TO RESTART", 17, 54, 440);
}

void loose(){
    play = false;
    print_text("WASTED", 6, 159, 400);
    print_text("RETURN TO RESTART", 17, 54, 440);
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

void resolveGroundHit(){
    // set ball red
    setBallColor(64);
    removeLive();
    setBallOnPad();
}

void resolvePadHit(){
    if (ball.vy > 0)
        ball.vy *= -1;

    /*
    // renvoie dans la direction du côté du pad qui à été touché
    if (((x_vault + srcVaiss.w / 2) - ball.x) > 0) {
        if (ball.vx > 0)
            ball.vx *= -1;
        else if (ball.vx < 0)
            ball.vx *= -1;
    }
     */
}


// fonction qui met à jour la surface de la fenetre "win_surf"
void draw() {
    // Dessine le fond
    print_background();
    // Dessine les briques
    print_bricks();

    // deplacement de la balle
    ball.x += (ball.vx / delta_t);
    ball.y += (ball.vy / delta_t);

    // collision pad
    if (ball.y > win_surf->h - 52 - ball.rayon / 2 && ball.y < win_surf->h - 52) {
        if (ball.x > x_vault && ball.x < x_vault + srcVaiss.w) {
            resolvePadHit();
        }
    }

    // collision bord
    if ((ball.x < 1)) {
        if (ball.vx < 0) {
            ball.vx *= -1;
        }
    }
    if(ball.x > (win_surf->w - ball.rayon / 2)){
        if (ball.vx > 0) {
            ball.vx *= -1;
        }
    }

    // touche haut
    if (ball.y < 1){
        if (ball.vy < 0) {
            ball.vy *= -1;
        }
    }

    // touche bas
    if (ball.y > (win_surf->h - ball.rayon / 2)) {
        resolveGroundHit();
    }

    // deplacement vaisseau
    dest.x = x_vault;
    dest.y = win_surf->h - 52;

    // gameStarted == false : la balle suit le vaisseau sur l'axe des X
    if (!gameStarted) {
        ball.x = x_vault + srcVaiss.w / 2 - ball.rayon / 2;
    }

    // Dessine la balle
    print_ball();
    // Dessine le vaisseau
    print_vaisseau();
    // Dessine les vies
    print_lives();
    // Dessine le score
    print_score(score);
}