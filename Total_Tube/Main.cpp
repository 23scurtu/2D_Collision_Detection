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

#define PI 3.14159265

using namespace std;

vector<float> project_square;
vector<float> project_triangle;
vec tempvect;
vec collidervect;
vec tempvect_norm;
vec unittempvect_norm;
bool collide = true;
int sleeptime = 3;

int main()
{
	sf::Event event;

	sf::RenderWindow window(sf::VideoMode(1000, 500), "SFML Application");

	poly triangle;
	poly square;

	//triangle.x = { 0, 220, 200 };
	//triangle.y = { 110, 150, 200 };
	triangle.originx = 175;
	triangle.originy = 175;

	square.x = { 300, 400, 400, 300 };
	square.y = { 300, 300, 400, 400 };
	//square.originx = 0;
	//square.originy = 0;

	triangle.isconvex();
	float tempx;

	while (window.isOpen())
	{
		window.clear();

		window.pollEvent(event);

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left) // male mouse button release
			{
				triangle.x.push_back(event.mouseButton.x);
				triangle.y.push_back(event.mouseButton.y);
		
				triangle.isconvex();
				triangle.createSubPolys();
				Sleep(250);
			}
		}

		if (GetAsyncKeyState(0x41))
		{
			for (int i = 0; i < triangle.x.size(); i++)
			{
				tempx = triangle.x[i];
				triangle.x[i] = (triangle.x[i] - triangle.originx)* cos(PI / 180) - (triangle.y[i] - triangle.originy) * sin(PI / 180) + triangle.originx;
				triangle.y[i] = (triangle.y[i] - triangle.originy)* cos(PI / 180) + (tempx - triangle.originx) * sin(PI / 180) + triangle.originy;
			}
		}
		if (GetAsyncKeyState(0x44))
		{
			for (int i = 0; i < triangle.x.size(); i++)
			{
				tempx = triangle.x[i];
				triangle.x[i] = (triangle.x[i] - triangle.originx)* cos(-PI / 180) - (triangle.y[i] - triangle.originy) * sin(-PI / 180) + triangle.originx;
				triangle.y[i] = (triangle.y[i] - triangle.originy)* cos(-PI / 180) + (tempx - triangle.originx) * sin(-PI / 180) + triangle.originy;
			}
		}

		if (GetAsyncKeyState(VK_LEFT))
		{
			for (int i = 0; i < triangle.x.size(); i++)
			{
				triangle.x[i]--;
			}	
			triangle.originx--;
		}

		if (GetAsyncKeyState(VK_RIGHT))
		{
			for (int i = 0; i < triangle.x.size(); i++)
			{
				triangle.x[i]++;
			}
			triangle.originx++;
		}
		if (GetAsyncKeyState(VK_UP))
		{
			for (int i = 0; i < triangle.x.size(); i++)
			{
				triangle.y[i]--;
			}
			triangle.originy--;
		}

		if (GetAsyncKeyState(VK_DOWN))
		{
			for (int i = 0; i < triangle.x.size(); i++)
			{
				triangle.y[i]++;
			}
			triangle.originy++;
		}
		if (triangle.iscollide(square))
		{
			triangle.drawSolid(window, sf::Color::Red);
		}
		else
		{
			triangle.drawSolid(window, sf::Color::Green);
		}
		if (event.type == sf::Event::Closed) window.close();

		square.drawSolid(window, sf::Color::Green);
		window.display();
		Sleep(sleeptime);
	}
	return 0;
}