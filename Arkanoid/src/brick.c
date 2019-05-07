#include "brick.h"


Brick_color getColorFromChar(char c){
    Brick_color brickColor;
    switch (c){
        case '0':
            brickColor = BLANC;
            break;
        case '1':
            brickColor = ORANGE;
            break;
        case '2':
            brickColor = BLEU_CLAIR;
            break;
        case '3':
            brickColor = VERT;
            break;
        case '4':
            brickColor = ROUGE;
            break;
        case '5':
            brickColor = BLEU;
            break;
        case '6':
            brickColor = ROSE;
            break;
        case '7':
            brickColor = JAUNE;
            break;
        case '8':
            brickColor = GRIS;
            break;
        case '9':
            brickColor = OR;
            break;
        default:
            brickColor = TRANSPARENT;
            break;
    }
    return brickColor;
}

void load_brick_from_file(const char *path) {

    row_nbr = 13;
    column_nbr = 20;
    //brick_list = malloc(row_nbr * column_nbr * sizeof(BRICK));


    brick_list = malloc(sizeof *brick_list * row_nbr );
    if(brick_list){
        for (size_t i = 0; i < row_nbr; i++)
        {
            brick_list[i] = malloc(sizeof *brick_list[i] * column_nbr);
        }
    }


    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(path, "r");
    if (fp == NULL)
        printf("ERROR fp is NULL");

    //BRICK b = {1 * 33, 1 * 16, VERT};

    //brick_list[0][0] = b;


    size_t row = 0;

    while ((read = getline(&line, &len, fp)) != -1) {
        // printf("Retrieved line of length %zu:\n", read);
        //printf("%s", line);

        for (size_t i = 0; i < read; i++){
            if(line[i] != '\n'){
                BRICK b = {i * ( win_surf->w / 13 ) , row * 16, getColorFromChar(line[i])};
                brick_list[i][row] = b;
            }
        }
        row++;
    }

    //while ((read = getline(&line, &len, fp)) != -1) {
    //    // printf("Retrieved line of length %zu:\n", read);
    //    // printf("%s", line);
    //    for (size_t i = 0; i < read; i++){
    //    BRICK b = {i * 33, i * 16, VERT};
    //    brick_list[0][i] = b;
    //    }
    //}
    // brick_list[0][0] = b;
    fclose(fp);
    if (line)
        free(line);

}