#include "Weapon.h"



Weapon::Weapon()
{
}

Weapon::~Weapon()
{

}

void Weapon::copyData(Weapon* inventory)
{
	InventoryInHand::copyData(inventory);
	inventory->setWeaponDamage(weaponDamage);
}

