#include "Vectors.h"

vec::vec()
	:x(0.f), y(0.f){};

float vec::mag()
{
	return sqrt(pow(x, 2) + pow(y, 2));
}

float vec::cross(vec second)
{
	return x*second.y - y*second.x;
}

void vec::set(float x, float y)
{
	this->x = x;
	this->y = y;
}
vec::vec(int x, int y)
{
	this->x = x;
	this->y = y;
}

bool vec::isBetween(vec vec1, vec vec2) // checks to see if a vector is between two other vectors. (space between two vectors is the vector created when subtracting vec1 and vec2)
{
	if (cross(vec1) == 0 || cross(vec2) == 0) return true;

	if (cross(vec1) < 0 && cross(vec2) > 0) return true;
	else if (cross(vec1) > 0 && cross(vec2) < 0) return true;

	return false;
}