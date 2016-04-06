#include <iostream>
#include <string>
#include <Windows.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <math.h>
#include "Poly.h"
#include "Utils.h"
#include "Vectors.h"
#include <vector> 

#define PI 3.14159265

using namespace std;

vector<float> project_obsticle;
vector<float> project_testShape;
vec tempvect;
vec collidervect;
vec tempvect_norm;
vec unittempvect_norm;
bool collide = true;
int sleeptime = 3;
float moveSpeed = 1;

int main()
{
	sf::Event event;

	sf::RenderWindow window(sf::VideoMode(1000, 500), "SFML Application");

	poly testShape;
	poly obsticle;

	//testShape.x = { 0, 220, 200 };
	//testShape.y = { 110, 150, 200 };
	testShape.xOrigin = 175;
	testShape.yOrigin = 175;

	obsticle.x = { 300, 400, 400, 300 };
	obsticle.y = { 300, 300, 400, 400 };
	//obsticle.originx = 0;
	//obsticle.originy = 0;

	testShape.isconvex();
	float tempx;

	vector<float> x;
	vector<float> y;

	while (window.isOpen())
	{
		window.clear();

		window.pollEvent(event);

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left) // male mouse button release
			{
				testShape.x.push_back(event.mouseButton.x);
				testShape.y.push_back(event.mouseButton.y);
		
				testShape.isconvex();
				testShape.createConvexPolys();

				Sleep(250);
			}
		}
		
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Right) // male mouse button release
			{
				cout << "(" << event.mouseButton.x << "," << event.mouseButton.y << ")" << endl;
			}
		}

		if (GetAsyncKeyState(0x41))
		{
			testShape.rotate(0.01);

		}
		if (GetAsyncKeyState(0x44))
		{
			testShape.rotate(-0.01);
		}

		if (GetAsyncKeyState(VK_LEFT))
		{
			testShape.xTranslate(-moveSpeed);
		}

		if (GetAsyncKeyState(VK_RIGHT))
		{
			testShape.xTranslate(moveSpeed);
		}
		if (GetAsyncKeyState(VK_UP))
		{
			testShape.yTranslate(-moveSpeed);
		}

		if (GetAsyncKeyState(VK_DOWN))
		{
			testShape.yTranslate(moveSpeed);
		}

		if (testShape.isCollide(obsticle))
		{
			testShape.drawSolid(window, sf::Color::Red);
		}
		else
		{
			testShape.drawSolid(window, sf::Color::Green);
		}
		if (event.type == sf::Event::Closed) window.close();

		obsticle.drawConvexSolid(window, sf::Color::Green);

		/*if (testShape.subPolys.size() > 0)
		{
			testShape.subPolys[0].drawConvexSolid(window, sf::Color::Blue);
		}*/

		window.display();
		Sleep(sleeptime);
	}
	return 0;
}
