#include "brick.h"

void load_brick_from_file(const char* path){
	brick_number = 13;
	brick_list = (BRICK*)malloc(brick_number * sizeof(BRICK));
	for (size_t i = 0; i < brick_number; i++){
		BRICK b = {i * 33, 0, VERT};
		brick_list[i] = b;
	}
}