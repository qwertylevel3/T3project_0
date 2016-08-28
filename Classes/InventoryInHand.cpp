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
	character->setLeftHand(this);
}

void InventoryInHand::unequipLeftHand(Character* character)
{
	character->setLeftHand(nullptr);
}

void InventoryInHand::equipRightHand(Character* character)
{
	character->setRightHand(this);
}

void InventoryInHand::unequipRightHand(Character* character)
{
	character->setRightHand(nullptr);
}


void InventoryInHand::copyData(InventoryInHand* inventory)
{
	Inventory::copyData(inventory);

	inventory->setStrRequire(strRequire);
	inventory->setAgiRequire(agiRequire);
	inventory->setIntRequire(intRequire);
}
