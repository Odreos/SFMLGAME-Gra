#include "EnemyManager.hpp"

EnemyManager::EnemyManager(vector<Enemy*>* enemies)
{
	this->enemies = enemies;
}

void EnemyManager::AddEnemy(Enemy* e)
{
	enemies->push_back(e);
}

void EnemyManager::DeleteEnemy(int id)
{
	enemies->erase(
		remove_if(
			enemies->begin(),
			enemies->end(),
			[id](Enemy* e) {return e->GetID() == id; }
		),
		enemies->end());
}

void EnemyManager::ClearEnemiesVec()
{
	enemies->clear();
}

void EnemyManager::Update(float dt)
{
	for (auto& e : *enemies)
	{
		e->Uptade(dt);
	}
}

void EnemyManager::Draw(RenderWindow& window)
{
	for (auto& e : *enemies)
	{
		e->Draw(window);
	}
}
