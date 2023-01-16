#pragma once
#include "Enemy.hpp"
#include "SFML/Graphics.hpp"
#include <vector>

using namespace std;
using namespace sf;

class EnemyManager
{
public:
	vector<Enemy>* enemies;

	EnemyManager(vector<Enemy>* enemies);
	void AddEnemy(Enemy* e);
	void Update(float dt);
};

