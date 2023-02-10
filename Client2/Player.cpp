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

	player.setSize({ PLAYER_SIZE ,PLAYER_SIZE });
	player.setOrigin(player.getSize() / 2.f);

	laserPointCircle.setFillColor(Color::Green);
	laserPointCircle.setRadius(5);
	laserPointCircle.setPosition({ 0,0 });
	laserPointCircle.setOrigin(laserPointCircle.getRadius(), laserPointCircle.getRadius());


	muzzleTXT.loadFromFile(PLAYER_MUZZLE);

	muzzle.SetAmountAnimations(4);
	muzzle.SetSpeed(0.1);
	muzzle.SetTxt(&muzzleTXT, 4);
	isReadyForGameplay = 0;
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
	if (getMovingState())
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
}

void Player::setVelo(Vector2f ve)
{
	velo = ve;
}

void Player::setPlayerTxt(Texture& t)
{
	playerTXT = &t;
	player.setTexture(playerTXT);
}

void Player::setDir(PlayerDirection d)
{
	dir = d;
}

Vector2f Player::getVelo()
{
	return velo;
}

PlayerDirection Player::getDir()
{
	return dir;
}

void Player::setMovingState(bool ty)
{
	isMoving = ty;
}

void Player::SetCorrectPosByDT(double dt)
{
	Vector2f playerPos = getPos();
	cout << "Przed: " << playerPos.x << " " << playerPos.y;
	switch (dir)
	{
	case MoveUp: // up
	{
		playerPos.y = playerPos.y + (playerPos.y*-dt);
	}
	break;
	case MoveDown: // down
	{
		playerPos.y = playerPos.y + (playerPos.y * dt);
	}
	break;
	case MoveLeft: // left
	{
		playerPos.x = playerPos.x + (playerPos.x * -dt);
	}
	break;
	case MoveRight: // right
	{
		playerPos.x = playerPos.x + (playerPos.x * dt);
	}
	break;
	default:
		break;
	}

	setPos(playerPos);
	cout << " po: " << playerPos.x << " " << playerPos.y << endl;
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

void Player::update(double dt)
{

	float pAngleRad = (player.getRotation() - 90) / 180 * M_PI;

	Vector2f pos = { player.getPosition().x + cosf(pAngleRad) * player.getSize().x/2, player.getPosition().y + sinf(pAngleRad) * player.getSize().y/2 };

	laserPointCircle.setPosition(pos);
	muzzle.SetPos(pos);
	muzzle.SetAngle(player.getRotation());
	muzzle.Update(dt);

	if (weapon.isReloading)
	{
		muzzle.Stop();
	}
	else
	{
		if (weapon.shooting)
			muzzle.Play();
	}
	weapon.Update(dt);
}

void Player::draw(RenderWindow& w)
{
	w.draw(player);
	if (weapon.isLaserOn)
		w.draw(weapon.laser);
	if (muzzle.play)
		muzzle.Draw(w);
}
