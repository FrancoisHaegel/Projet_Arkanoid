void colliding()
{
	if(ceil(((ball)/32)<13)&&ceil(((ball)/16)<20))
	{
		int col = ceil((ball.x)/32);
		int row = ceil((ball.y)/16);
		if(brick_list[row][col].bc > 0) resolveCollision(brick_list[row][col]);
	}
}

void resolveCollision(Brick brick)
{
    ball.vy = -ball.vy;
    brick.bc = 0;
}
