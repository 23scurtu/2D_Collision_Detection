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
bool intersect(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, vector<float> & x, vector<float> & y) // replace: too manyperameters
{
	if (x2 - x1 != 0 && x4 - x3 != 0) // check effets on rest of program, find root
	{
		float m1 = (y2 - y1) / (x2 - x1);
		float m2 = (y4 - y3) / (x4 - x3);
		float c1 = y1 - m1*x1;
		float c2 = y3 - m2*x3;

		if (m1 - m2 == 0)
		{
			cerr << "Error: no intersection for intersect function." << endl;
			return false;
		}
		else
		{
			x.push_back((c2 - c1) / (m1 - m2));
			y.push_back(m1 * x.back() + c1);
			return true;
		}
	}
}