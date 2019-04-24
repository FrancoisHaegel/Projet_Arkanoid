#include "utils.h"

// Return a char array representing the int in parameter
char * toArray(const int number)
{
	char * ns = (char*)malloc(5 * sizeof(char));
	sprintf(ns,"%05d",number);
	return ns;
}