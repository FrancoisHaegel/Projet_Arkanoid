#include "print.h"

SDL_Surface *plancheSprites = NULL;
SDL_Surface *plancheASCIISprites = NULL;
SDL_Surface *plancheArkanoidSprites = NULL;

SDL_Rect srcBg = {0, 128, 96, 128}; // x,y, w,h (0,0) en haut a gauche
SDL_Rect srcBall = {0, 96, 24, 24};
SDL_Rect srcVaiss = {128, 0, 128, 32};
SDL_Rect dest = {0, 0, 0, 0};


void init_print(void) {
    plancheSprites = SDL_LoadBMP(OTHER_SPRITE_PATH);
    SDL_SetColorKey(plancheSprites, true, 0);  // 0: 00/00/00 noir -> transparent
    plancheASCIISprites = SDL_LoadBMP(ASCII_SPRITE_PATH);
    SDL_SetColorKey(plancheASCIISprites, true, 0);  // 0: 00/00/00 noir -> transparent
    plancheArkanoidSprites = SDL_LoadBMP(ARKANOID_SPRITE_PATH);
    SDL_SetColorKey(plancheArkanoidSprites, true, 0);  // 0: 00/00/00 noir -> transparent
}

void print_ascii(const char c, const int x, const int y) {
    SDL_Rect src = {0, 0, 17, 20}; // x,y, w,h (0,0) en haut a gauche
    switch (c) {
        case '0':
            src.x = 2;
            src.y = 38;
            break;
        case '1':
            src.x = 34;
            src.y = 38;
            break;
        case '2':
            src.x = 66;
            src.y = 38;
            break;
        case '3':
            src.x = 98;
            src.y = 38;
            break;
        case '4':
            src.x = 130;
            src.y = 38;
            break;
        case '5':
            src.x = 163;
            src.y = 38;
            break;
        case '6':
            src.x = 194;
            src.y = 38;
            break;
        case '7':
            src.x = 226;
            src.y = 38;
            break;
        case '8':
            src.x = 258;
            src.y = 38;
            break;
        case '9':
            src.x = 290;
            src.y = 38;
            break;
        case 'A':
            src.x = 32 * 1;
            src.y = 6 + 32 * 2;
            break;
        case 'B':
            src.x = 32 * 2;
            src.y = 6 + 32 * 2;
            break;
        case 'C':
            src.x = 32 * 3;
            src.y = 6 + 32 * 2;
            break;
        case 'D':
            src.x = 32 * 4;
            src.y = 6 + 32 * 2;
            break;
        case 'E':
            src.x = 32 * 5;
            src.y = 6 + 32 * 2;
            break;
        case 'F':
            src.x = 32 * 6;
            src.y = 6 + 32 * 2;
            break;
        case 'G':
            src.x = 32 * 7;
            src.y = 6 + 32 * 2;
            break;
        case 'H':
            src.x = 32 * 8;
            src.y = 6 + 32 * 2;
            break;
        case 'I':
            src.x = 32 * 9;
            src.y = 6 + 32 * 2;
            break;
        case 'J':
            src.x = 32 * 10;
            src.y = 6 + 32 * 2;
            break;
        case 'K':
            src.x = 32 * 11;
            src.y = 6 + 32 * 2;
            break;
        case 'L':
            src.x = 32 * 12;
            src.y = 6 + 32 * 2;
            break;
        case 'M':
            src.x = 32 * 13;
            src.y = 6 + 32 * 2;
            break;
        case 'N':
            src.x = 32 * 14;
            src.y = 6 + 32 * 2;
            break;
        case 'O':
            src.x = 32 * 15;
            src.y = 6 + 32 * 2;
            break;
        case 'P':
            src.x = 32 * 0;
            src.y = 6 + 32 * 3;
            break;
        case 'Q':
            src.x = 32 * 1;
            src.y = 6 + 32 * 3;
            break;
        case 'R':
            src.x = 32 * 2;
            src.y = 6 + 32 * 3;
            break;
        case 'S':
            src.x = 32 * 3;
            src.y = 6 + 32 * 3;
            break;
        case 'T':
            src.x = 32 * 4;
            src.y = 6 + 32 * 3;
            break;
        case 'U':
            src.x = 32 * 5;
            src.y = 6 + 32 * 3;
            break;
        case 'V':
            src.x = 32 * 6;
            src.y = 6 + 32 * 3;
            break;
        case 'W':
            src.x = 32 * 7;
            src.y = 6 + 32 * 3;
            break;
        case 'X':
            src.x = 32 * 8;
            src.y = 6 + 32 * 3;
            break;
        case 'Y':
            src.x = 32 * 9;
            src.y = 6 + 32 * 3;
            break;
        case 'Z':
            src.x = 32 * 10;
            src.y = 6 + 32 * 3;
            break;
    }
    SDL_Rect destASCII = {x, y, 0, 0};
    drawAt(plancheASCIISprites, &src, &destASCII);
}

// affiche le score
void print_score(const int score) {
    char *arr_score = toArray(score);
    for (size_t i = 0; i < 5; i++) {
        print_ascii(arr_score[i], i * 18 + 20, 20);
    }
}


// Imprime le charArray de taille size à partir des positions x et y, la largeur du texte est size * 20 px
void print_text(const char* charArray, const size_t size, const int x, const int y){
    for (size_t i = 0; i < size; i++) {
        print_ascii(charArray[i], i * 20 + x, y);
    }
}

// remplit le fond
void print_background(void) {
    for (int j = 0; j < win_surf->h; j += 128)
        for (int i = 0; i < win_surf->w; i += 96) {
            dest.x = i;
            dest.y = j;
            drawAt(plancheSprites, &srcBg, &dest);
        }
}

// affiche balle
void print_ball(void) {
    SDL_Rect dstBall = {ball.x - ball.rayon/2, ball.y - ball.rayon/2, 0, 0};
    drawAt(plancheSprites, &srcBall, &dstBall);
}

// affiche le vaisseau
void print_vaisseau(void) {
    drawAt(plancheSprites, &srcVaiss, &dest);
}

int epoqueBrick = 0; // 0-5 représente le sprite a afficher pour les briques brillantes
SDL_Rect getBrickSprite(const Brick_color *bc) {
    SDL_Rect res = {0, 0, 32, 16}; // x,y, w,h (0,0) en haut a gauche
    switch (*bc) {
        case BLANC:
            res.x = 0 * res.w;
            res.y = 0;
            break;
        case ORANGE:
            res.x = 1 * res.w;
            res.y = 0;
            break;
        case BLEU_CLAIR:
            res.x = 2 * res.w;
            res.y = 0;
            break;
        case VERT:
            res.x = 3 * res.w;
            res.y = 0;
            break;
        case ROUGE:
            res.x = 0 * res.w;
            res.y = 1 * res.h;
            break;
        case BLEU:
            res.x = 1 * res.w;
            res.y = 1 * res.h;
            break;
        case ROSE:
            res.x = 2 * res.w;
            res.y = 1 * res.h;
            break;
        case JAUNE:
            res.x = 3 * res.w;
            res.y = 1 * res.h;
            break;
        case GRIS:
            res.x = epoqueBrick * res.w;
            res.y = 2 * res.h;
            break;
        case OR:
            res.x = epoqueBrick * res.w;
            res.y = 3 * res.h;
            break;
    }
    if (epoqueBrick == 4) { epoqueBrick = -1;}
    //else { epoqueBrick++; }
    return res;
}

void print_bricks(void) {
    for (size_t x = 0; x < row_nbr; x++) {
        for (size_t y = 0; y < column_nbr; y++) {
            if (brick_list[x][y].bc != TRANSPARENT) {
                SDL_Rect src = getBrickSprite(&brick_list[x][y].bc);
                SDL_Rect dest = {brick_list[x][y].x, brick_list[x][y].y, 50, src.h};
                drawAt(plancheArkanoidSprites, &src, &dest);
            }
        }
    }
}

void print_lives(void){
    SDL_Rect src = {384, 127, 64, 16}; // x,y, w,h (0,0) en haut a gauche
    for (int i = 0; i < nbLives; ++i) {
        SDL_Rect dest = {i * 70 + 10, win_surf->h - 20, 64, 16};
        drawAt(plancheArkanoidSprites, &src, &dest);
    }
}

void setBallColor(unsigned int color){
    srcBall.y = color;
}

void setBallOnPad(){
    ball.y = win_surf->h - 52 - ball.rayon * 2;
    ball.x = x_vault + ball.rayon;
    gameStarted = false;
    ball.vx = 0.0;
    ball.vy = 0.0;
}
