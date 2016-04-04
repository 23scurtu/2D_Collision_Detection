#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <iostream>
#include "Vectors.h"

using namespace std;

float maxval(vector<float> a);
float minval(vector<float> a);
bool intersect(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, vector<float> &x, vector<float> &y); //finds intersection of two lines and store in vectors
//make intersect() pass vector rather than 8 coord perameters

#endif 