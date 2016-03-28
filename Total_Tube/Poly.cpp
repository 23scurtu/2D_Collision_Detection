#include <iostream>
#include <Windows.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <math.h>
#include "Poly.h"
#include "Utils.h"
#include "Vectors.h"

#define PI 3.14159265

using namespace std;

poly::poly()
{

}


bool poly::iscollide(poly testshape)
{
	vec tempvect;
	vec tempvect_norm;
	vector<float> project_second;
	vector<float> project_first;
	vec unittempvect_norm;

	if (x.size() < 3 || testshape.x.size() < 3) return false; // temp to deal with non shapes

	for (int i = 0; i < x.size(); i++)
	{
		if (i != x.size() - 1)
		{
			tempvect.set(x[i + 1] - x[i], y[i + 1] - y[i]);
		}
		
		else
		{
			tempvect.set(x[0] - x[i], y[0] - y[i]);
		}

		tempvect_norm.set(-tempvect.y, tempvect.x);// make norm function

		unittempvect_norm.set(tempvect_norm.x / tempvect_norm.mag(), tempvect_norm.y / tempvect_norm.mag());

		for (int i = 0; i != x.size(); i++)
		{
			project_first.push_back(x[i] * unittempvect_norm.x + y[i] * unittempvect_norm.y);

		}
		for (int i = 0; i != testshape.x.size(); i++)
		{
			project_second.push_back(testshape.x[i] * unittempvect_norm.x + testshape.y[i] * unittempvect_norm.y);

		}

		if (minval(project_first) > maxval(project_second) || minval(project_second) > maxval(project_first))
		{

			return false;

		}

		project_first.clear();
		project_second.clear();
		

	}

	for (int i = 0; i < testshape.x.size(); i++)
	{
		if (i != testshape.x.size() - 1)
		{
			tempvect.set(testshape.x[i + 1] - testshape.x[i], testshape.y[i + 1] - testshape.y[i]);
		}
		else
		{
			tempvect.set(testshape.x[0] - testshape.x[i], testshape.y[0] - testshape.y[i]);
		}

		tempvect_norm.set(-tempvect.y, tempvect.x);


		//include norms into vecs

		unittempvect_norm.set(tempvect_norm.x / tempvect_norm.mag(), tempvect_norm.y / tempvect_norm.mag());

		for (int i = 0; i != x.size(); i++)
		{
			project_first.push_back(x[i] * unittempvect_norm.x + y[i] * unittempvect_norm.y);

		}
		for (int i = 0; i != testshape.x.size(); i++)
		{
			project_second.push_back(testshape.x[i] * unittempvect_norm.x + testshape.y[i] * unittempvect_norm.y);

		}

		if (minval(project_first) > maxval(project_second) || minval(project_second) > maxval(project_first))
		{

			return false;

		}

		project_first.clear();
		project_second.clear();
	}

	return true;
}

void poly::drawSolid(sf::RenderWindow &window, sf::Color color)
{
	sf::ConvexShape convex;
	convex.setFillColor(color);

	convex.setPointCount(x.size());

	for (int i = 0; i != x.size(); i++)
	{
		convex.setPoint(i, sf::Vector2f(x[i], y[i]));
	}
	window.draw(convex);
}

void poly::calcSides()
{
	sides.clear(); // MAKE BETTER?
	for (int i = 0; i < x.size() - 1; i++)
	{
		sides.push_back(vec(x[i + 1] - x[i], y[i + 1] - y[i]));
		//cout << x[i + 1] - x[i] << endl;
		//cout << y[i + 1] - y[i] << endl << endl;
	}
	sides.push_back(vec(x[0] - x[x.size() - 1], y[0] - y[y.size() - 1]));
	//cout << x[0] - x[x.size() - 1] << endl;
	//cout << y[0] - y[y.size() - 1] << endl << endl;
}

bool poly::isconvex()
{
	
	if (x.size() > 2)
	{
		calcSides();
		reflexAngles.clear(); // make better

		if (sides[sides.size() - 1].cross(sides[0]) < 0)
		{
			reflexAngles.push_back(0);
			cout << "DONE";
		}
		for (int i = 0; i != sides.size() - 1; i++)
		{
			if (sides[i].cross(sides[i + 1]) < 0) reflexAngles.push_back(i + 1);
		}
	}

	if (reflexAngles.size() == 0) 
		return false;
	else return true;
}

void poly::createSubPolys()
{
	vector<float> xintersects;
	vector<float> yintersects;

	if (x.size() > 2 && reflexAngles.size() > 0) // no need 4 sides, is only acheck to see if isconvex was done or calc sides
	{
		//for (int i = 0; i != reflexAngles.size(); i++) // attentions start at 0
		//{

			//int &r = reflexAngles[i]; // temp alias to make lines shorter

		int &r = reflexAngles[0];  // cmbine find reflex anglesto make find first reflex angle function and ind number of reflx angles



			if (r == 0) // maybe incorperate into bottom one
			{
				for (int u = 1; u < x.size() - 2; u++)
				{
					if (sides[sides.size() - 1].isBetween(vec(x[u] - x[r], y[u] - y[r]), vec(x[u + 1] - x[r], y[u + 1] - y[r])))
					{
						intersect(x[x.size() - 1],
							   	  y[y.size() - 1],
								  x[0],
								  y[0],
								  x[u],
								  y[u],
								  x[u+1],
								  y[u+1],
								  xintersects,
								  yintersects);

						cout << u + 1 << " lmao ";
					}
				}
				
			}
			else
			{
				for (int u = 0; u < r - 2; u++)
				{
					if (sides[r - 1].isBetween(vec(x[u] - x[r], y[u] - y[r]), vec(x[u + 1] - x[r], y[u + 1] - y[r])))
					{
						intersect(x[r - 1], //  check
								  y[r - 1],
								  x[r],
								  y[r],
								  x[u],
								  y[u],
								  x[u + 1],
								  y[u + 1],
								  xintersects,
								  yintersects);

						cout << u + 1 << " exdee ";
					}
	
				}
				for (int u = r + 1; u < x.size() - 1; u++)
				{
					if (sides[r - 1].isBetween(vec(x[u] - x[r], y[u] - y[r]), vec(x[u + 1] - x[r], y[u + 1] - y[r])))
					{
						intersect(x[r - 1], //  check
								  y[r - 1],
								  x[r],
								  y[r],
								  x[u],
								  y[u],
								  x[u + 1],
								  y[u + 1],
								  xintersects,
								  yintersects);
						cout << u + 1 << " lol ";
					}
				}
				if (r != x.size() - 1 && r != 1)
				{
					if (sides[r - 1].isBetween(vec(x[x.size() - 1] - x[r], y[x.size() - 1] - y[r]), vec(x[0] - x[r], y[0] - y[r])))
					{
						intersect(x[r - 1], //  check
								  y[r - 1],
								  x[r],
								  y[r],
								  x[x.size() - 1],
								  y[x.size() - 1],
								  x[0],
								  y[0],
								  xintersects,
								  yintersects);

						cout <<  x.size()  << " haha ";
					}
				}
			}
			for (int i = 0; i < xintersects.size(); i++)
			{
				cout << "(" << xintersects[i] << "," << yintersects[i] << endl;
			}

		//}
	}
	cout << endl;
}

/*  
	float m1, c1, m2, c2;
    float x1, y1, x2, y2;
    float dx, dy;
    float intersection_X, intersection_Y;

    dx = x2 - x1;
    dy = y2 - y1;
 
    m1 = dy / dx;
    // y = mx + c
    // intercept c = y - mx
    c1 = y1 - m1 * x1; // which is same as y2 - slope * x2
 
    if( (m1 - m2) == 0)
        std::cout << "No Intersection between the lines\n";
    else
    {
        intersection_X = (c2 - c1) / (m1 - m2);
        intersection_Y = m1 * intersection_X + c1;
    }
*/

