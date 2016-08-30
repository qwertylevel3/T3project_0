#include "Weapon.h"



Weapon::Weapon()
{
	atkArea = new WeaponAtkArea();
}

Weapon::~Weapon()
{
	delete atkArea;
}

void Weapon::copyData(Weapon* inventory)
{
	InventoryInHand::copyData(inventory);
	inventory->setWeaponDamage(weaponDamage);
	atkArea->copyAtkAreaData(inventory->getAtkAreaPtr());
}

void Weapon::addAtkAreaPoint(cocos2d::Point point)
{
	atkArea->addPosition(point);
}

std::vector<cocos2d::Point> Weapon::getAtkArea(Character* attacker)
{
	return atkArea->getAtkArea(attacker);
}


WeaponAtkArea* Weapon::getAtkAreaPtr()
{
	return atkArea;
}

