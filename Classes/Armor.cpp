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

	newArmor->setArmorCount(armorCount);

	return newArmor;
}
