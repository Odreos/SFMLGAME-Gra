#include "Weapon.hpp"

Weapon::Weapon()
{
	firerate = 0.05;
	enableToShot = 0;
	timerToShot = 0;
	damage = 30;

	isReloading = 0;
	timerToReload = 2;
	forceToReload = 0;

	allAmmo = 120;
	maxAmmoInMag = 30;
	currentAmmo = 30;

	senInfoAfterReload = 0;
	isReloadingForCheck = 0;
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

void Weapon::SetDefaultInfo()
{
	firerate = 0.05;
	enableToShot = 0;
	timerToShot = 0;
	damage = 30;

	isReloading = 0;
	timerToReload = 2;
	forceToReload = 0;

	allAmmo = 120;
	maxAmmoInMag = 30;
	currentAmmo = 30;

	senInfoAfterReload = 0;
	isReloadingForCheck = 0;
}

bool Weapon::Fire()
{
	if(shooting)
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

bool Weapon::SetForceToReload()
{
	if (currentAmmo != maxAmmoInMag)
	{
		forceToReload = 1;
		return true;
	}
	else
		return false;
	return false;
}

void Weapon::Reload()
{
	if (allAmmo > 0)
		if(currentAmmo != maxAmmoInMag)
			if (currentAmmo == 0 || forceToReload)
			{
				isReloading = 1;
				senInfoAfterReload = 0;
				isReloadingForCheck = 1;
			}
}

void Weapon::Update(float dt)
{
	Reload();

	if (!enableToShot)
	{
		timerToShot += dt;
		if (timerToShot > firerate)
		{
			enableToShot = 1;
			timerToShot -= firerate;

		}
	}

	if (isReloading)
	{
		currnetTimeToReload += dt;
		if (currnetTimeToReload > timerToReload)
		{
			isReloading = 0;
			currnetTimeToReload = 0;
			if (forceToReload) forceToReload = 0;

			int diff = maxAmmoInMag - currentAmmo;

			if (allAmmo >= diff)
			{
				allAmmo -= diff;
				currentAmmo += diff;
			}
			else
			{
				currentAmmo += allAmmo;
				allAmmo = 0;
			}

			senInfoAfterReload = 1;

		}
	}
}
