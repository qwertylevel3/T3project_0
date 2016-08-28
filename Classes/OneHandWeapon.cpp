#include "OneHandWeapon.h"



OneHandWeapon::OneHandWeapon()
{
}


OneHandWeapon::~OneHandWeapon()
{
}

OneHandWeapon* OneHandWeapon::clone()
{
	OneHandWeapon* weapon = new OneHandWeapon();
	copyData(weapon);
	return weapon;
}

void OneHandWeapon::copyData(OneHandWeapon* inventory)
{
	Weapon::copyData(inventory);
	inventory->setInventoryType(Inventory::OneHandWeapon);
}
