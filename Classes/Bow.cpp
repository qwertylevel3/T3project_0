#include "Bow.h"
#include "Character.h"



Bow::Bow()
{
}


Bow::~Bow()
{
}

void Bow::equipLeftHand(Character* character)
{
	character->unequipLeftHand();
	character->unequipRightHand();
	character->setLeftHand(this);
	character->setRightHand(this);
}

void Bow::unequipLeftHand(Character* character)
{

}

void Bow::equipRightHand(Character* character)
{
	character->unequipLeftHand();
	character->unequipRightHand();
	character->setLeftHand(this);
	character->setRightHand(this);
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
