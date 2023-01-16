#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <iostream>

using namespace std;
using namespace sf;

class Weapon
{
public:

	float firerate;
	bool enableToShot;
	float timerToShot;
	bool forceToReload;
	float timerToReload;
	bool isReloading;
	int currentAmmo;
	int allAmmo;
	int maxAmmoInMag;
	float currnetTimeToReload;
	bool shooting;
	bool isLaserOn;
	Vector2f laserPoint;

	RectangleShape laser;

	Vector2f mousePos;
	Vector2f playerPos;
	string ammoAndMagInfo;
	Weapon();
	int* GetCurrentAmmo();
	int* GetAllAmmo();
	int* GetMaxAmmoInMag();
	void SetAllAmmo(int x);
	void SetCurrentAmmo(int x);
	void SetDefaultInfo();
	void SetLaser(bool x);
	void SetLaserPoint(Vector2f playerPos, Vector2f point, float playerAngle);
	void SetReloading(bool x);
	//void SetForceToReload();
	//void Reload();
	bool Fire();
	void Update(float dt);
};

