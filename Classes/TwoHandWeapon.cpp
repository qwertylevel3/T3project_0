#include "TwoHandWeapon.h"
#include "Character.h"



TwoHandWeapon::TwoHandWeapon()
{
}


TwoHandWeapon::~TwoHandWeapon()
{
}

void TwoHandWeapon::equipLeftHand(Character* character)
{
	character->unequipLeftHand();
	character->unequipRightHand();
	character->setLeftHand(this);
	character->setRightHand(this);
}

void TwoHandWeapon::unequipLeftHand(Character* character)
{

}

void TwoHandWeapon::equipRightHand(Character* character)
{
	character->unequipLeftHand();
	character->unequipRightHand();
	character->setLeftHand(this);
	character->setRightHand(this);
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
