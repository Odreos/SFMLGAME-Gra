#include "Ball.hpp"

Ball::Ball()
{
	id = -1;
	ball.setFillColor(Color::Red);
	ball.setRadius(10);
	ball.setPosition({ 200,100 });
}

void Ball::setPos(Vector2f pos)
{
	ball.setPosition(pos);
}

void Ball::moveBall(Vector2f m)
{
	Vector2f newVelo = { speed.x * m.x,speed.y * m.y };

	ball.move(newVelo);
}

void Ball::setSpeed(Vector2f s)
{
	speed = s;
}

void Ball::setID(int ID)
{
	id = ID;
}

int Ball::getID()
{
	return id;
}

void Ball::draw(RenderWindow* w)
{
	w->draw(ball);
}
