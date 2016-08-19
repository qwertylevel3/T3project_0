#pragma once

#include"Inventory.h"
#include "platform/CCPlatformMacros.h"

class Armor:public Inventory
{
public:
	Armor();
	~Armor();
protected:
	CC_SYNTHESIZE(int, armorCount, ArmorCount);
};

