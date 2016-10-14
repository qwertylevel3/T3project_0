#include "Bow.h"



Bow::Bow()
{
}


Bow::~Bow()
{
}

void Bow::equipLeftHand(Character* character)
{

}

void Bow::unequipLeftHand(Character* character)
{

}

void Bow::equipRightHand(Character* character)
{

}

void Bow::unequipRightHand(Character* character)
{

}

Bow* Bow::clone()
{
	Bow* weapon = new Bow();
	copyData(weapon);
	return weapon;
}

void Bow::copyData(Bow* inventory)
{
	Weapon::copyData(inventory);
	inventory->setInventoryType(Inventory::Bow);
}
