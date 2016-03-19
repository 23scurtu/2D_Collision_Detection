#include "Utils.h"
#include "Vectors.h"

float maxval(vector<float> a)
{
	float max = a[0];

	for (int i = 0; i != a.size(); i++)
	{
		if (a[i] > max) max = a[i];
	}
	return max;
}

float minval(vector<float> a)
{
	float min = a[0];

	for (int i = 0; i != a.size(); i++)
	{
		if (a[i] < min) min = a[i];
	}
	return min;
}
