#include "Player.hpp"

Player::Player(int ID, Vector2f velo, Vector2f pos)
{
	setID(ID);
	setVelo(velo);
	setPos(pos);
}

Player::Player()
{
	setOnline(false);
	setVelo({ PLAYER_SPEED,PLAYER_SPEED });
	setDir(PlayerDirection::MoveRight);
	setID(-1);
	setPos({ 100,100 });
	player.setFillColor(Color::Red);
	player.setSize({ PLAYER_SIZE ,PLAYER_SIZE });
	player.setOrigin(player.getSize() / 2.f);

	isEnemyCloser = 0;
	isWallCloser = 0;
	readyForGameplay = 0;
}

void Player::setID(int ID)
{
	playerID = ID;
}

int Player::getID()
{
	return playerID;
}

void Player::setPos(Vector2f pos)
{
	player.setPosition(pos);
}

Vector2f Player::getPos()
{
	return player.getPosition();
}

void Player::movePlayer(double dt)
{
	Vector2f newVelo({ velo.x * (float)dt, velo.y * (float)dt });

	switch (dir)
	{
	case MoveUp: // up
	{
		newVelo.x = 0;
		newVelo.y = newVelo.y * -1;
	}
	break;
	case MoveDown: // down
	{
		newVelo.x = 0;
	}
	break;
	case MoveLeft: // left
	{
		newVelo.x = newVelo.x * -1;
		newVelo.y = 0;
	}
	break;
	case MoveRight: // right
	{
		newVelo.y = 0;
	}
	break;
	default:
		break;
	}

	player.move(newVelo);
}

void Player::setVelo(Vector2f ve)
{
	velo = ve;
}

Vector2f Player::getVelo()
{
	return velo;
}

Vector2f Player::getWeaponPos()
{
	return { 0,0 }; //TODO
}

void Player::setDir(PlayerDirection d)
{
	dir = d;
}

PlayerDirection Player::getDir()
{
	return dir;
}

void Player::setMovingState(bool ty)
{
	isMoving = ty;
}

void Player::setPlayerAngle(float a)
{
	player.setRotation(a);
}

float Player::getPlayerAngle()
{
	return player.getRotation();
}

bool Player::getMovingState()
{
	return isMoving;
}

void Player::setOnline(bool t)
{
	isOnline = t;
}

bool Player::getOnline()
{
	return isOnline;
}
