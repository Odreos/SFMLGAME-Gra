#include "EnemyManager.hpp"

EnemyManager::EnemyManager(vector<Enemy>* enemies)
{
	this->enemies = enemies;
}

void EnemyManager::AddEnemy(Enemy* e)
{
	enemies->push_back(*e);
}

void EnemyManager::Update(float dt)
{
	for (auto& e : *enemies)
	{
		e.Uptade(dt);
	}
}
