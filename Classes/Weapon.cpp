#include "Weapon.h"
#include "WeaponSphereHandler.h"
#include "SphereBase.h"



Weapon::Weapon()
{
	sphereHandler = new WeaponSphereHandler();
}

Weapon::~Weapon()
{
	delete sphereHandler;
}

void Weapon::copyData(Weapon* inventory)
{
	InventoryInHand::copyData(inventory);
	for each (Sphere::SphereBase* sphere in sphereHandler->getSphereBoxRef())
	{
		inventory->addSphere(sphere->getID());
	}
	inventory->setWeaponDamage(weaponDamage);
}

void Weapon::addSphere(const std::string& sphereID)
{
	sphereHandler->addSphere(sphereID);
}

WeaponSphereHandler* Weapon::getSphereHandler()
{
	return sphereHandler;
}

