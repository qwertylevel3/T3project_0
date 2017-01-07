#pragma once

#include"Inventory.h"
#include "platform/CCPlatformMacros.h"

class Armor:public Inventory
{
public:
	Armor();
	~Armor();
	void equipArmor(Character* character);
	Armor* clone();
protected:
	std::string getExtraDescription();
	CC_SYNTHESIZE(int, armorCount, ArmorCount);
};

