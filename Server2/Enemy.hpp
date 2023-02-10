#pragma once
#include <SFML/Graphics.hpp>
#include <queue>
#include <iostream>
#include "Definitions.hpp"

using namespace std;
using namespace sf;

enum EnemyDirection
{
	MoveUpE,
	MoveDownE,
	MoveLeftE,
	MoveRightE
};

class Enemy
{
public:
	RectangleShape enemy;
	int enemyID;
	queue<int> mapTileIDToMove;
	vector<int> mapTileIDToMoveVector;
	int acutalMovingTileID;
	Vector2f startPosMoving;
	Vector2f endPosMoving;
	EnemyDirection dir;
	Vector2f velo;
	bool isOnEndPos;
	bool isMoving;
	float enemyHP;

	Enemy();
	void SetPos(Vector2f pos);
	const Vector2f& GetPos();
	void SetID(int id);
	const int& GetID();
	void AddIDToTileMove(vector<int> ids);
	Vector2f GetTilePosByID(int id);
	void moveByTileID(float dt);
	float GetEnemyHP();
	void SetEnemyHP(float x);
	void Move(float dt);
	void SetPosByTileID(int id);
	bool getMovingState();
	void Uptade(float dt);
	void Draw(RenderWindow& window);
};

