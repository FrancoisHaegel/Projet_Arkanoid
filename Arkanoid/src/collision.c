#include "collision.h"
#include <math.h>

void colliding(){
	 if(ceil(((ball.y)/16)<20))
 	{
 		int col = (int)((ball.x + ball.rayon)/32);
		int row = (int)(((ball.y + ball.rayon)/16));
	  //check if a brick is at this location
		if(col > -1 && col < 13 && row > -1 && row < 20){
			if(brick_list[col][row].bc != TRANSPARENT){
	 			resolveCollision(&brick_list[col][row]);
	 		}
		}
	}
}

void resolveCollision(BRICK* brick){

	 	double ballCenterX = ball.x + ball.rayon;
		double ballCenterY = ball.y + ball.rayon;

		// if(brick->x - ball.rayon <= ballCenterX && ballCenterX <= brick->x + ball.rayon + 32){
		// 	ball.vy = ball.vy * (-1);
		//   brick->bc = TRANSPARENT;
		// }else if(brick->y - ball.rayon <= ballCenterY && ballCenterY <= brick->y + ball.rayon + 16){
		// 	ball.vx = ball.vx * (-1);
		//   brick->bc = TRANSPARENT;
		// }


		
		double brickCenterX = brick->x + 16;
		double brickCenterY = brick->y + 8;
		//si on touche sur le bas de la brique
		if(ballCenterY > brickCenterY + 8){
			ball.vy = ball.vy * (-1);
	    brick->bc = TRANSPARENT;
		}
		//si on touche le haut de la brique
		else if(ballCenterY < brickCenterY - 8){
			ball.vy = ball.vy * (-1);
	    brick->bc = TRANSPARENT;
		}
		//si on touche la gauche de la brique
		else if(ballCenterX > brickCenterX + 16){
			ball.vx = ball.vx * (-1);
	    brick->bc = TRANSPARENT;
		}
		//si on touche la droite de la brique
		else{
			ball.vx = ball.vx * (-1);
	    brick->bc = TRANSPARENT;
		}
}
