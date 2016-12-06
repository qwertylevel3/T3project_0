#include "Weapon.h"
#include "WeaponSphereHandler.h"
#include "SphereBase.h"
#include "ToolFunction.h"
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

std::string Weapon::getExtraDescription()
{
	std::string description;
	description += ToolFunction::WStr2UTF8(L"基础伤害:")
		+ "+" + ToolFunction::int2string(weaponDamage) + "\n\n";

	std::vector<Sphere::SphereBase*>& allSphere = sphereHandler->getSphereBoxRef();

	if (allSphere.empty())
	{
		return description;
	}



	description	+= ToolFunction::WStr2UTF8(L"法球效果:\n");

	int count=1;
	for each (Sphere::SphereBase* sphere in allSphere)
	{
		description += ToolFunction::int2string(count) + "."+
			sphere->getDescription() + "\n";
		count++;
	}
	return description;
}