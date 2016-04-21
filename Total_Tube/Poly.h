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

		bool isConvexCollide(poly testshape); // coldies convexHull
		bool isCollide(poly testshape); // used colides subPolys

		float xOrigin;
		float yOrigin;
		void drawConvexSolid(sf::RenderWindow &window, sf::Color color);
		void drawSolid(sf::RenderWindow &window, sf::Color color);
		bool isconvex();
		void splitReflex();
		void calcSides();
		void rotatePoly(float rad, float originx, float originy);
		void rotate(float rad);
		void xTranslate(float input);
		void yTranslate(float input);
		void createConvexPolys();
		//make translate func accepting vector for later physics
		//make class for concave polys that inherites poly?
};



#endif 