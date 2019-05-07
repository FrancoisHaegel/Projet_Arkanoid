#include "collision.h"
#include <math.h>

void colliding(){
	 if(ceil(((ball.y)/16)<20))
 	{
 		int col = (int)((ball.x)/46);
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
}
