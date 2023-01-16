#include "Bullet.hpp"

Bullet::Bullet()
{
	bullet.setFillColor(Color::White);
	bullet.setRadius(3);
	bullet.setOrigin(bullet.getRadius(), bullet.getRadius());

	velo = { BULLET_SPEED,BULLET_SPEED };
}

void Bullet::SetDirection(Vector2f dir)
{
	direction = dir;
}

void Bullet::SetPos(Vector2f pos)
{
	bullet.setPosition(pos);
}

Vector2f Bullet::GetPos()
{
	return bullet.getPosition();
}

void Bullet::SetID(int ID)
{
	id = ID;
}

int Bullet::GetID()
{
	return id;
}

void Bullet::SetOwnerID(int id)
{
	ownerID = id;
}

int Bullet::GetOwnerID()
{
	return ownerID;
}

void Bullet::moveBullet(float dt)
{
	Vector2f newVelo({ direction.x * velo.x * (float)dt, direction.y * velo.y * (float)dt });
	bullet.move(newVelo);
}
