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


bool poly::isConvexCollide(poly testshape)
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

		for (int i = 0; i != x.size(); i++) // fix reapearing i
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

void poly::drawConvexSolid(sf::RenderWindow &window, sf::Color color)
{
	sf::ConvexShape convex;
	convex.setFillColor(color);

	convex.setOutlineThickness(1);
	
	convex.setOutlineColor(sf::Color::Black);

	convex.setPointCount(x.size());

	for (int i = 0; i != x.size(); i++)
	{
		convex.setPoint(i, sf::Vector2f(x[i], y[i]));
	}
	window.draw(convex);
}

void poly::drawSolid(sf::RenderWindow &window, sf::Color color) // handles whether convex or not but uses isconvex, better?
{
    if (isconvex())
    {
        drawConvexSolid(window, color);
    }
    else
    {
        for (int i = 0; i != subPolys.size(); i++)
        {
            subPolys[i].drawConvexSolid(window, color);
        }
    }
}

void poly::calcSides()
{
	sides.clear(); // MAKE BETTER?
	for (int i = 0; i < x.size() - 1; i++)
	{
		sides.push_back(vec(x[i + 1] - x[i], y[i + 1] - y[i]));
	}
	sides.push_back(vec(x[0] - x[x.size() - 1], y[0] - y[y.size() - 1]));
}

bool poly::isconvex()
{

	if (x.size() > 2)
	{
		calcSides();
		reflexAngles.clear(); // better method?

		if (sides[sides.size() - 1].cross(sides[0]) < 0)
		{
			reflexAngles.push_back(0);
		}
		for (int i = 0; i != sides.size() - 1; i++)
		{
			if (sides[i].cross(sides[i + 1]) < 0) reflexAngles.push_back(i + 1);
		}
	}

	if (reflexAngles.size() == 0)
		return true;
	else return false;
}

void poly::splitReflex()
{
	vector<float> xintersects;
	vector<float> yintersects;
	float xsplit;
	float ysplit;
	int splitPos;
	vector<int> pos;

	if (x.size() > 3 && reflexAngles.size() > 0) // no need 4 sides, is only acheck to see if isconvex was done or calc sides
	{

		int &r = reflexAngles[0];

			if (r == 0)
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
						
						pos.push_back(u);
					}
					
				}


				for (int i = 0; i != xintersects.size(); i++) // make function
				{
					if ((x[r] - x[x.size() - 1])*(xintersects[i] - x[x.size() - 1]) < 0 || (y[r] - y[x.size() - 1])*(yintersects[i] - y[x.size() - 1]) < 0)
					{
						xintersects.erase(xintersects.begin() + i);
						yintersects.erase(yintersects.begin() + i);
						pos.erase(pos.begin() + i);

						i = 0; // costly.
					}
				}


			}
			else
			{
				for (int u = 0; u < r - 2; u++)
				{
					if (sides[r - 1].isBetween(vec(x[u] - x[r], y[u] - y[r]), vec(x[u + 1] - x[r], y[u + 1] - y[r])))
					{
						intersect(x[r - 1],
								  y[r - 1],
								  x[r],
								  y[r],
								  x[u],
								  y[u],
								  x[u + 1],
								  y[u + 1],
								  xintersects,
								  yintersects);

						pos.push_back(u);
					}

				}
				for (int u = r + 1; u < x.size() - 1; u++)
				{
					if (sides[r - 1].isBetween(vec(x[u] - x[r], y[u] - y[r]), vec(x[u + 1] - x[r], y[u + 1] - y[r])))
					{
						intersect(x[r - 1],
								  y[r - 1],
								  x[r],
								  y[r],
								  x[u],
								  y[u],
								  x[u + 1],
								  y[u + 1],
								  xintersects,
								  yintersects);

						pos.push_back(u);
					}
				}
				if (r != x.size() - 1 && r != 1)
				{
					if (sides[r - 1].isBetween(vec(x[x.size() - 1] - x[r], y[x.size() - 1] - y[r]), vec(x[0] - x[r], y[0] - y[r])))
					{
						intersect(x[r - 1],
								  y[r - 1],
								  x[r],
								  y[r],
								  x[x.size() - 1],
								  y[x.size() - 1],
								  x[0],
								  y[0],
								  xintersects,
								  yintersects);

						pos.push_back(x.size() - 1);
					}
				}
				
				for (int i = 0; i != xintersects.size(); i++)
				{
					if ((x[r] - x[r - 1])*(xintersects[i] - x[r - 1]) < 0 || (y[r] - y[r - 1])*(yintersects[i] - y[r - 1]) < 0)
					{
						xintersects.erase(xintersects.begin() + i);
						yintersects.erase(yintersects.begin() + i);
						pos.erase(pos.begin() + i);

                        i = 0; //inefficient
					}
				}
			}

			vector<float> tempmags; // replace use of vector

			for (int i = 0; i != xintersects.size(); i++)
			{
				tempmags.push_back(vec(x[r] - xintersects[i], y[r] - yintersects[i]).mag());
			}

            xsplit = xintersects[0];
            ysplit = yintersects[0];
            splitPos = pos[0];

			for (int i = 1; i != tempmags.size(); i++)
			{
				if (tempmags[i] < tempmags[i - 1])
				{
					xsplit = xintersects[i];
					ysplit = yintersects[i];
					splitPos = pos[i];
				}
			}

			poly  first, second;


			if (r < splitPos)
			{
				first.x.push_back(xsplit);
				first.y.push_back(ysplit);

				for (int i = splitPos + 1; i != x.size(); i++)
				{
					first.x.push_back(x[i]);
					first.y.push_back(y[i]);
				}
				for (int i = 0; i != r; i++)
				{
					first.x.push_back(x[i]);
					first.y.push_back(y[i]);
				}

				for (int i = r; i != splitPos + 1; i++)
				{
					second.x.push_back(x[i]);
					second.y.push_back(y[i]);
				}

				second.x.push_back(xsplit);
				second.y.push_back(ysplit);
			}
			else
			{
				first.x.push_back(xsplit);
				first.y.push_back(ysplit);

				for (int i = splitPos + 1; i != r; i++)
				{
					first.x.push_back(x[i]);
					first.y.push_back(y[i]);
				}

				for (int i = r; i != x.size(); i++)
				{
					second.x.push_back(x[i]);
					second.y.push_back(y[i]);
				}
				for (int i = 0; i != splitPos + 1; i++)
				{
					second.x.push_back(x[i]);
					second.y.push_back(y[i]);
				}

				second.x.push_back(xsplit);
				second.y.push_back(ysplit);
			}

			subPolys.push_back(first);
			subPolys.push_back(second);

	} // watch for split pos bugs
}

void poly::rotatePoly(float rad, float xOrigin, float yOrigin) // doesnt inlcude subPolys
{
	float cosine = cos(rad);
	float sine = sin(rad);


	for (int i = 0; i < x.size(); i++)
	{
		float tempx = x[i];
		x[i] = (x[i] - xOrigin)* cosine - (y[i] - yOrigin) * sine + xOrigin;
		y[i] = (y[i] - yOrigin)* cosine + (tempx - xOrigin) * sine + yOrigin;
	}
}

void poly::rotate(float rad) //include subPolys
{
	rotatePoly(rad, xOrigin, yOrigin);

	if (subPolys.size() > 0)
	{
		for (int i = 0; i != subPolys.size(); i++)
		{
			subPolys[i].rotatePoly(rad, xOrigin, yOrigin);
		}
	}
}

void poly::xTranslate(float input)
{
	xOrigin += input;

	for (int i = 0; i != x.size(); i++)
	{
		x[i] += input;
	}

	if (subPolys.size() != 0)
	{
		for (int u = 0; u != subPolys.size(); u++)
		{
			for (int i = 0; i != subPolys[u].x.size(); i++)
			{
				subPolys[u].x[i] += input;
			}
		}
	}
}
void poly::yTranslate(float input)
{
	yOrigin += input;

	for (int i = 0; i != x.size(); i++)
	{
		y[i] += input;
	}

	if (subPolys.size() != 0)
	{
		for (int u = 0; u != subPolys.size(); u++)
		{
			for (int i = 0; i != subPolys[u].x.size(); i++)
			{
				subPolys[u].y[i] += input;
			}
		}
	}
}
bool poly::isCollide(poly testshape)
{
	if (testshape.subPolys.size() == 0 && subPolys.size() == 0)
	{
		return isConvexCollide(testshape);
	}
	else if (subPolys.size() == 0)
	{
		for (int u = 0; u != testshape.subPolys.size(); u++)
		{
			if (testshape.subPolys[u].isConvexCollide(*this)) return true;
		}
	}
	else if (testshape.subPolys.size() == 0)
	{
		for (int u = 0; u != subPolys.size(); u++)
		{
			if (subPolys[u].isConvexCollide(testshape)) return true;
		}
	}
	else
	{
		for (int u = 0; u != subPolys.size(); u++)
		{
			for (int i = 0; i != testshape.subPolys.size(); i++)
			{
				if (subPolys[u].isConvexCollide(testshape.subPolys[i])) return true;
			}
		}
	}
	

	return false;
}

void poly::createConvexPolys()
{
	subPolys.clear();

	splitReflex();

	vector<poly> concaves, next, temp;


	for (int i = 0; i != subPolys.size(); i++)
	{
		if (subPolys[i].isconvex())
		{
			temp.push_back(subPolys[i]);
		}
		else
		{
			concaves.push_back(subPolys[i]);
		}
	}

	subPolys = temp;

	while (concaves.size() != 0)
	{
		for (int i = 0; i != concaves.size(); i++)
		{
			concaves[i].splitReflex();

			if (concaves[i].subPolys[0].isconvex())
			{
				subPolys.push_back(concaves[i].subPolys[0]);
			}
			else
			{
				next.push_back(concaves[i].subPolys[0]);
			}

			if (concaves[i].subPolys[1].isconvex())
			{
				subPolys.push_back(concaves[i].subPolys[1]);
			}
			else
			{
				next.push_back(concaves[i].subPolys[1]);
			}
		}
		concaves = next;
		next.clear();
	}
}



