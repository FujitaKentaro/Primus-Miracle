#include "WeaponsFactory.h"
#include "Weaponlist.h"

Weapon* WeaponsFactory::CleateScene(const std::string& sceneName)
{
	Weapon* newWeapon = nullptr;

	if (sceneName == "ASSAULT") {
		newWeapon = new Shotgun();
	}if (sceneName == "SHOTGUN") {
		newWeapon = new Assault();
	}if (sceneName == "BOMFIRE") {
		newWeapon = new BomFire();
	}
	else {
		return newWeapon;
	}
}
