//
// Created by nantoni on 07/05/19.
//

#include "gameManager.h"

//ancienne coordonée X du pad
int* padPreviousPosX;

void init() {
    gameStarted = false;
    play = true;
    score = 0;
    nbLives = 3;
    nbLevel = 3;
    currentLevel = 0;

    padPreviousPosX = malloc(5*sizeof(int));

    padPreviousPosX[0] = 0;
    padPreviousPosX[1] = 0;
    padPreviousPosX[2] = 0;
    padPreviousPosX[3] = 0;
    padPreviousPosX[4] = 0;

    init_draw();
    init_print();
    init_bonus();
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
          colliding(delta_t);
          collisionBonus(x_vault, srcVaiss.w);
          draw();
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
    bonus_number = 0;
    currentLevel = 0;
    nextLevel();
    play = true;
}

void win(){
    play = false;
    print_text("CONGRATULATION", 14, 68, 400);
    print_text("RETURN TO RESTART", 17, 38, 440);
    print_text("ESCAPE TO QUIT", 14, 68, 480);
}

void loose(){
    play = false;
    print_text("WASTED", 6, 148, 400);
    print_text("RETURN TO RESTART", 17, 38, 440);
    print_text("ESCAPE TO QUIT", 14, 68, 480);
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
    if (ball.vy > 0){
      //ball.vx *= (1+computePadSpeed());
      ball.vy *= -(1-computePadSpeed());
      ball.vx *= (1+computePadSpeed());
    }
}

//permet de calculer la vitesse du pad en fonction de sa position actuelle et de sa position à la frame précédente
double computePadSpeed(){
    double res = 0;
    if(padPreviousPosX[4] < padPreviousPosX[0]){
       res = ((double)padPreviousPosX[0] - (double)padPreviousPosX[4])/416;
     }else if(padPreviousPosX[4] > padPreviousPosX[0]){
       res = -((double)padPreviousPosX[4] - (double)padPreviousPosX[0])/416;
     }
    return res;
}

void resolveCollisionBonus(BONUS* bonus){
    switch (bonus->bt){
        case S:
            break;
    }
    unspawn_bonus(bonus);
}

void collisionBonus(int x_vault, int w_vault){
    for (int i = 0; i < bonus_number; ++i) {
        if(bonus_list[i].y + 16 > win_surf->h - 52 && bonus_list[i].y < win_surf->h - 36){
            addScore(1);
            if(bonus_list[i].x + 32 > x_vault - (w_vault / 2) && bonus_list[i].x < x_vault + (w_vault / 2)){
                addScore(1);
                resolveCollisionBonus(&bonus_list[i]);
            }
        }
    }
}


// fonction qui met à jour la surface de la fenetre "win_surf"
void draw() {

    // Dessine le fond
    print_background();
    // Dessine les briques
    print_bricks();

    padPreviousPosX[4] = padPreviousPosX[3];
    padPreviousPosX[3] = padPreviousPosX[2];
    padPreviousPosX[2] = padPreviousPosX[1];
    padPreviousPosX[1] = padPreviousPosX[0];
    padPreviousPosX[0] = x_vault;

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

    // Dessine les bonus
    print_bonuses();
    // Dessine la balle
    print_ball();
    // Dessine le vaisseau
    print_vaisseau();
    // Dessine les vies
    print_lives();
    // Dessine le score
    print_score(score);
}
