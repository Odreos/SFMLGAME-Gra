#pragma once

#include <SFML/System.hpp>

using namespace sf;

class MovePoint
{
public:

	Vector2f point;
	Vector2f velo;

	int pointID;
	MovePoint(Vector2f pos);
	Vector2f getPos();
	void movePoint(Vector2f m);
	void setVelo(Vector2f pos);
	int getID();
	void setID(int id);
};

