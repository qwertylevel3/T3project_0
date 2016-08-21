#pragma once

#include"Inventory.h"
#include "platform/CCPlatformMacros.h"

class Armor:public Inventory
{
public:
	Armor();
	~Armor();
	Armor* clone();
protected:
	CC_SYNTHESIZE(int, armorCount, ArmorCount);
};

