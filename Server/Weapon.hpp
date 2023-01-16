#pragma once

#include "Bullet.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <iostream>

using namespace std;
using namespace sf;

class Weapon
{
public:

	vector<Bullet*>* bullets;
	float firerate;
	bool enableToShot;
	float timerToShot;
	bool forceToReload;
	float timerToReload;
	bool isReloading;
	bool isReloadingForCheck;
	int currentAmmo;
	int allAmmo;
	int maxAmmoInMag;
	float currnetTimeToReload;
	bool shooting;
	bool senInfoAfterReload;
	int damage;

	Vector2f mousePos;
	Vector2f playerPos;
	Weapon();
	int* GetCurrentAmmo();
	int* GetAllAmmo();
	int* GetMaxAmmoInMag();
	void SetBulletVector(vector<Bullet*>* b);
	void AddBullet(Bullet* b);
	void SetAllAmmo(int x);
	void SetDefaultInfo();
	//bool Fire(Vector2f playerPos, Bullet* b);
	bool Fire();
	bool SetForceToReload();
	void Reload();
	void Update(float dt);
};

