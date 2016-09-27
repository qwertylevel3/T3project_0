#include "InventoryInHand.h"
#include "Character.h"



InventoryInHand::InventoryInHand()
{
	setInventoryType(Type::OneHandWeapon);
}



InventoryInHand::~InventoryInHand()
{

}

void InventoryInHand::equipLeftHand(Character* character)
{
	character->unequipLeftHand();
	character->setLeftHand(this);
}

void InventoryInHand::unequipLeftHand(Character* character)
{
}

void InventoryInHand::equipRightHand(Character* character)
{
	character->unequipRightHand();
	character->setRightHand(this);
}

void InventoryInHand::unequipRightHand(Character* character)
{
}


void InventoryInHand::copyData(InventoryInHand* inventory)
{
	Inventory::copyData(inventory);

	inventory->setStrRequire(strRequire);
	inventory->setAgiRequire(agiRequire);
	inventory->setIntRequire(intRequire);
}
