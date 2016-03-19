#ifndef VECTORS_H
#define VECTORS_H

#include <iostream>

using namespace std;

class vec
{

public:
	float x;
	float y;
	vec();
	vec(int x, int y);
	float mag();
	float cross(vec second); // maybe make crossproductsign
	void set(float x, float y);
	bool isBetween(vec vec1, vec vec2);
};

#endif 