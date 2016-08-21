#include "Weapon.h"



Weapon::Weapon()
{
	setInventoryType(Type::Weapon);
}


Weapon::~Weapon()
{
}

void Weapon::equip(Character* character)
{
}

void Weapon::unequip(Character* character)
{
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
