#ifndef POLY_H
#define POLY_H

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Vectors.h"

using namespace std;

class poly
{
		vector<vec> sides;
		vector<int> reflexAngles;
		//vector<poly> subPolys; // make if convex a bool
	public:
		vector<poly> subPolys; // make if convex a bool
		poly();
		vector<float> x;
		vector<float> y;

		bool iscollide(poly testshape); // clean up pl0x

		int originx;
		int originy;
		void drawConvexSolid(sf::RenderWindow &window, sf::Color color);
		void drawSolid(sf::RenderWindow &window, sf::Color color);
		bool isconvex();
		void splitReflex();
		void calcSides();
		void rotatePoly(float rad, int originx, int originy);
		void rotate(float rad);
};


#endif 