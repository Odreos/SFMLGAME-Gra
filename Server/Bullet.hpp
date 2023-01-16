#pragma once
#include <SFML/Graphics.hpp>
#include "Definitions.hpp"

using namespace sf;

class Bullet
{
public:
	CircleShape bullet;
	Vector2f velo;
	Vector2f direction;
	int id;
	int ownerID;
	Bullet();

	void SetDirection(Vector2f dir);
	void SetPos(Vector2f pos);
	Vector2f GetPos();
	void SetID(int ID);
	int GetID();
	void SetOwnerID(int id);
	int GetOwnerID();
	void moveBullet(float dt);
};

