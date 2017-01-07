#include "Armor.h"
#include "ToolFunction.h"
#include "Character.h"



Armor::Armor()
{
	setInventoryType(Inventory::Armor);
}


Armor::~Armor()
{
}

void Armor::equipArmor(Character* character)
{
	character->unequipArmor();
	character->setArmor(this);
}

Armor* Armor::clone()
{
	Armor* newArmor = new Armor();

	this->copyData(newArmor);

	newArmor->setInventoryType(Inventory::Armor);
	newArmor->setArmorCount(armorCount);

	return newArmor;
}

std::string Armor::getExtraDescription()
{
	std::string description;
	description += ToolFunction::WStr2UTF8(L"»¤¼×Öµ:")
		+ "+" + ToolFunction::int2string(armorCount) + "\n";

	return description;
}
