#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Definitions.hpp"
#include "Weapon.hpp"
#include "Animation.hpp"

using namespace std;
using namespace sf;

enum PlayerDirection
{
	MoveZero = -1,
	MoveUp,
	MoveDown,
	MoveLeft,
	MoveRight
};

class Player
{
public:
	RectangleShape player;
	Animation muzzle;
	Texture muzzleTXT;
	Texture* playerTXT;
	Vector2f velo;
	PlayerDirection dir;
	Weapon weapon;
	map<float, Vector2f> pointsOfLaserEndWalls;
	map<float, Vector2f> pointsOfLaserEndBots;
	CircleShape laserPointCircle;
	float lenghtForWalls = 0;
	float lenghtForBots = 0;
	RectangleShape* WallPlayerLookAt;
	CircleShape* BotPlayerLookAt;
	int playerID;
	int clientID;
	bool isMoving;
	bool isOnline;
	bool isReadyForGameplay;

	Player(int ID, Vector2f velo, Vector2f pos);
	Player();
	void setID(int ID);
	int getID();
	void setPos(Vector2f pos);
	Vector2f getPos();
	void movePlayer(double dt);
	void setVelo(Vector2f ve);
	void setPlayerTxt(Texture& t);
	void setDir(PlayerDirection d);
	Vector2f getVelo();
	PlayerDirection getDir();
	void setMovingState(bool ty);
	void SetCorrectPosByDT(double dt);
	bool getMovingState();
	void setOnline(bool t);
	bool getOnline();
	void update(double dt);
	void draw(RenderWindow& w);
};

