#include "TwoHandWeapon.h"



TwoHandWeapon::TwoHandWeapon()
{
}


TwoHandWeapon::~TwoHandWeapon()
{
}

void TwoHandWeapon::equipLeftHand(Character* character)
{

}

void TwoHandWeapon::unequipLeftHand(Character* character)
{

}

void TwoHandWeapon::equipRightHand(Character* character)
{

}

void TwoHandWeapon::unequipRightHand(Character* character)
{

}

TwoHandWeapon* TwoHandWeapon::clone()
{
	TwoHandWeapon* weapon = new TwoHandWeapon();
	copyData(weapon);

	return weapon;
}

void TwoHandWeapon::copyData(TwoHandWeapon* inventory)
{
	Weapon::copyData(inventory);
	inventory->setInventoryType(Inventory::TwoHandWeapon);
}
