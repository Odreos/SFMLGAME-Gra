#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Ball
{
public:
	CircleShape ball;
	Vector2f speed = { 0,100 };

	int id;

	Ball();
	void setPos(Vector2f pos);
	void moveBall(Vector2f m);
	void setSpeed(Vector2f s);
	void setID(int ID);
	int getID();
	void draw(RenderWindow* w);
};

