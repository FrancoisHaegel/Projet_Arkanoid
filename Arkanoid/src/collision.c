#include "collision.h"
#include <math.h>

void colliding(){
	 if(ceil(((ball.y)/16)<20))
 	{
 		int col = (int)((ball.x)/32);
		int row = (int)(((ball.y)/16));
	  //check if a brick is at this location
		 if(brick_list[col][row].bc != TRANSPARENT){
		resolveCollision(&brick_list[col][row]);
		}
	}
}

void resolveCollision(BRICK* brick){
    ball.vy = ball.vy * (-1);
    brick->bc = TRANSPARENT;

		// double brickCenterX = brick->x + 16;
		// double brickCenterY = brick->y + 8;
		//
		// double ballCenterX = ball.x + ball.rayon;
		// double ballCenterY = ball.y + ball.rayon;
		//
		// //si on touche sur le bas de la brique
		// if(ballCenterY > brickCenterY + 8){
		//
		// }
		// //si on touche le haut de la brique
		// else if(ballCenterY < brickCenterY - 8){
		//
		// }
		// //si on touche la gauche de la brique
		// else if(ballCenterX > brickCenterX + 16){
		//
		// }
		// //si on touche la droite de la brique
		// else{
		//
		// }
}
