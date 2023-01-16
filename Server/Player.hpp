#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include "Weapon.hpp"
#include "Definitions.hpp"
#include "Enemy.hpp"

using namespace sf;

enum PlayerDirection
{
	MoveUp,
	MoveDown,
	MoveLeft,
	MoveRight
};

class Player
{
public:
	RectangleShape player;
	Vector2f velo;
	PlayerDirection dir;
	Weapon weapon;

	Vector2f laserPoint;
	map<float, Vector2f> pointsOfLaserEndWalls;
	map<float, Vector2f> pointsOfLaserEndBots;
	float lenghtForWalls = 0;
	float lenghtForBots = 0;
	RectangleShape* WallPlayerLookAt;
	Enemy* EnemyPlayerLookAt;

	int playerID;
	int clientID;
	bool isMoving;
	bool isOnline;
	bool readyForGameplay;
	unsigned short UDPPort;

	bool isEnemyCloser;
	bool isWallCloser;

	Player(int ID, Vector2f velo, Vector2f pos);
	Player();
	void setID(int ID);
	int getID();
	void setPos(Vector2f pos);
	Vector2f getPos();
	void movePlayer(double dt);
	void setVelo(Vector2f ve);
	Vector2f getVelo();
	Vector2f getWeaponPos();
	void setDir(PlayerDirection d);
	PlayerDirection getDir();
	void setMovingState(bool ty);
	void setPlayerAngle(float a);
	float getPlayerAngle();
	bool getMovingState();
	void setOnline(bool t);
	bool getOnline();
};

