#include "Accessory.h"
#include "Character.h"



Accessory::Accessory()
{
	setInventoryType(Inventory::Accessory);
}


Accessory::~Accessory()
{
}

void Accessory::equipAccessory(Character* character)
{
	character->unequipAccessory();
	character->setAccessory(this);
}

Accessory* Accessory::clone()
{
	Accessory* newAccessory = new Accessory();

	this->copyData(newAccessory);

	newAccessory->setInventoryType(Inventory::Accessory);

	return newAccessory;
}
