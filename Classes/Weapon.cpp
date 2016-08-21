#include "Weapon.h"
#include "Character.h"



Weapon::Weapon()
{
	setInventoryType(Type::Weapon);
}


Weapon::~Weapon()
{
}

void Weapon::equipLeftHand(Character* character)
{
	character->setLeftHand(this);
}

void Weapon::unequipLeftHand(Character* character)
{
	character->setLeftHand(nullptr);
}

void Weapon::equipRightHand(Character* character)
{
	character->setRightHand(this);
}

void Weapon::unequipRightHand(Character* character)
{
	character->setRightHand(nullptr);
}

Weapon* Weapon::clone()
{
	Weapon* newWeapon = new Weapon();

	this->copyData(newWeapon);

	newWeapon->setWeaponDamage(weaponDamage);
	newWeapon->setStrRequire(strRequire);
	newWeapon->setAgiRequire(agiRequire);
	newWeapon->setIntRequire(intRequire);

	return newWeapon;
}
