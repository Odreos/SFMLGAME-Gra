#include "Weapon.hpp"

Weapon::Weapon()
{
	firerate = 0.05;
	enableToShot = 0;
	timerToShot = 0;

	isReloading = 0;
	timerToReload = 2;
	forceToReload = 0;

	allAmmo = 9999;
	maxAmmoInMag = 9999;
	currentAmmo = 9999;

	isLaserOn = 0;

	laser.setFillColor(Color::Green);
}

int* Weapon::GetCurrentAmmo()
{
	return &currentAmmo;
}

int* Weapon::GetAllAmmo()
{
	return &allAmmo;
}

int* Weapon::GetMaxAmmoInMag()
{
	return &maxAmmoInMag;
}

void Weapon::SetAllAmmo(int x)
{
	allAmmo = x;
}

void Weapon::SetCurrentAmmo(int x)
{
	currentAmmo = x;
}

void Weapon::SetDefaultInfo()
{
	firerate = 0.05;
	enableToShot = 0;
	timerToShot = 0;

	isReloading = 0;
	timerToReload = 2;
	forceToReload = 0;

	allAmmo = 9999;
	maxAmmoInMag = 9999;
	currentAmmo = 9999;
}

void Weapon::SetLaser(bool x)
{
	isLaserOn = x;
}

void Weapon::SetLaserPoint(Vector2f playerPos, Vector2f point, float playerAngle)
{
	Vector2f vec = playerPos - point;

	float lenght = sqrtf(pow(vec.x, 2) + pow(vec.y, 2));

	Vector2f vecNorm = vec / lenght;

	laser.setPosition(playerPos);
	laser.setSize({ 1, 1 * lenght });
	laser.setRotation(playerAngle + 180);
}

void Weapon::SetReloading(bool x)
{
	if (allAmmo > 0)
		isReloading = x;
}

bool Weapon::Fire()
{
	if (shooting)
		if (!isReloading)
			if (currentAmmo > 0)
			{
				if (enableToShot)
				{
					enableToShot = 0;
					currentAmmo--;
					return true;
				}
			}
	return false;
}

void Weapon::Update(float dt)
{
	ammoAndMagInfo = to_string(currentAmmo) + " / " + to_string(allAmmo);
}
