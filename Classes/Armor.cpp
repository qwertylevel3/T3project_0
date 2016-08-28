#include "Armor.h"



Armor::Armor()
{
	setInventoryType(Inventory::Armor);
}


Armor::~Armor()
{
}

Armor* Armor::clone()
{
	Armor* newArmor = new Armor();

	this->copyData(newArmor);

	newArmor->setInventoryType(Inventory::Armor);
	newArmor->setArmorCount(armorCount);

	return newArmor;
}
