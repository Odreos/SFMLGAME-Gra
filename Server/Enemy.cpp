#include "Enemy.hpp"

Enemy::Enemy()
{
	enemy.setSize({ PLAYER_SIZE, PLAYER_SIZE });
	enemy.setOrigin(enemy.getSize() / 2.f);
	enemy.setFillColor(Color::Red);

	acutalMovingTileID = -1;
	startPosMoving = endPosMoving = this->GetPos();
	velo = { ENEMY_SPEED,ENEMY_SPEED };
	isOnEndPos = 1;
}

void Enemy::SetPos(Vector2f pos)
{
	enemy.setPosition(pos);
	startPosMoving = endPosMoving = this->GetPos();
}

const Vector2f& Enemy::GetPos()
{
	return enemy.getPosition();
}

void Enemy::SetID(int id)
{
	enemyID = id;
}

const int& Enemy::GetID()
{
	return enemyID;
}

void Enemy::AddIDToTileMove(vector<int> ids)
{
	for (auto& i : ids)
	{
		mapTileIDToMove.push(i);
	}
}

Vector2f Enemy::GetTilePosByID(int id)
{
	Vector2f tilePos;
	tilePos.y = id / MAP_SIZE;
	tilePos.x = id % MAP_SIZE;

	tilePos = { tilePos.x * TILE_SIZE + TILE_SIZE/2, tilePos.y * TILE_SIZE + TILE_SIZE / 2 };
	return tilePos;
}

void Enemy::moveByTileID(float dt)
{
	if (!mapTileIDToMove.empty())
	{
		if (isOnEndPos)
		{
			isOnEndPos = 0;
			int tileID = mapTileIDToMove.front();
			if (tileID != acutalMovingTileID)
			{
				acutalMovingTileID = tileID;
				startPosMoving = endPosMoving;
				//cout << "start pos: " << startPosMoving.x << " " << startPosMoving.y << endl;
				endPosMoving = GetTilePosByID(tileID);
				//cout << "end pos: " << endPosMoving.x << " " << endPosMoving.y << endl;

				if (endPosMoving.x > startPosMoving.x)
					dir = EnemyDirection::MoveRightE;
				else if (endPosMoving.x < startPosMoving.x)
					dir = EnemyDirection::MoveLeftE;
				else if (endPosMoving.y > startPosMoving.y)
					dir = EnemyDirection::MoveDownE;
				else if (endPosMoving.y < startPosMoving.y)
					dir = EnemyDirection::MoveUpE;
				isMoving = 1;
			}
			else
			{
				return;
			}
		}
	}
}

float Enemy::GetEnemyHP()
{
	return enemyHP;
}

void Enemy::SetEnemyHP(float x)
{
	enemyHP = x;
}

void Enemy::Move(float dt)
{
	if (getMovingState())
	{
		Vector2f newVelo({ velo.x * (float)dt, velo.y * (float)dt });

		switch (dir)
		{
		case MoveUpE: // up
		{
			newVelo.x = 0;
			newVelo.y = newVelo.y * -1;
		}
		break;
		case MoveDownE: // down
		{
			newVelo.x = 0;
		}
		break;
		case MoveLeftE: // left
		{
			newVelo.x = newVelo.x * -1;
			newVelo.y = 0;
		}
		break;
		case MoveRightE: // right
		{
			newVelo.y = 0;
		}
		break;
		default:
			break;
		}

		Vector2f ePos = enemy.getPosition();
		Vector2f potentialPos = { ePos.x + newVelo.x, ePos.y + newVelo.y };

		switch (dir)
		{
		case MoveUpE: // up
		{
			if (potentialPos.y <= endPosMoving.y)
			{
				isOnEndPos = 1;
				isMoving = 0;
				mapTileIDToMove.pop();
				enemy.setPosition(endPosMoving);
			}
		}
		break;
		case MoveDownE: // down
		{
			if (potentialPos.y >= endPosMoving.y)
			{
				isOnEndPos = 1;
				isMoving = 0;
				mapTileIDToMove.pop();
				enemy.setPosition(endPosMoving);
			}
		}
		break;
		case MoveLeftE: // left
		{
			if (potentialPos.x <= endPosMoving.x)
			{
				isOnEndPos = 1;
				isMoving = 0;
				mapTileIDToMove.pop();
				enemy.setPosition(endPosMoving);
			}
		}
		break;
		case MoveRightE: // right
		{
			if (potentialPos.x >= endPosMoving.x)
			{
				isOnEndPos = 1;
				isMoving = 0;
				mapTileIDToMove.pop();
				enemy.setPosition(endPosMoving);
			}
		}
		break;
		default:
			break;
		}
		if (isMoving)
			enemy.move(newVelo);
	}
}

void Enemy::SetPosByTileID(int id)
{
	enemy.setPosition(GetTilePosByID(id));
	startPosMoving = endPosMoving = this->GetPos();
}

bool Enemy::getMovingState()
{
	return isMoving;
}

void Enemy::Uptade(float dt)
{
	moveByTileID(dt);
	Move(dt);
}

void Enemy::Draw(RenderWindow& window)
{
	window.draw(enemy);
}
