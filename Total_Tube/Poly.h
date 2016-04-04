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
		vector<poly> subPolys; // make if convex a bool
	public:
		poly();
		vector<float> x;
		vector<float> y;

		bool iscollide(poly testshape); // clean up pl0x

		int originx;
		int originy;
		void drawSolid(sf::RenderWindow &window, sf::Color color);
		bool isconvex();
		void createConvexPolys();
		void calcSides();
};


#endif 