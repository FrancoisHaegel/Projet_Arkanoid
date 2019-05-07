#include "collision.h"
#include <math.h>

void colliding(){
  //check if the ball is in the brick area
	if(ceil(((ball.x)/32)<13)&&ceil(((ball.y)/16)<20))
	{
		int col = ceil((ball.x)/32);
		int row = ceil((ball.y)/16);
    
    //check if a brick is at this location
		if(brick_list[row][col].bc > 0) resolveCollision(brick_list[row][col]);
	}
}

void resolveCollision(BRICK brick){
    ball.vy = ball.vy * (-1);
    brick.bc = 0;
}
