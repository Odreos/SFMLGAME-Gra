#include "MovePoint.hpp"

MovePoint::MovePoint(Vector2f pos)
{
	point = pos;
}

Vector2f MovePoint::getPos()
{
	return point;
}

void MovePoint::movePoint(Vector2f m)
{

	point.x += velo.x * m.x;
	point.y += velo.y * m.y;

}

void MovePoint::setVelo(Vector2f pos)
{
	velo = pos;
}

int MovePoint::getID()
{
	return pointID;
}

void MovePoint::setID(int id)
{
	pointID = id;
}
