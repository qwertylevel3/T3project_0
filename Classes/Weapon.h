#pragma once

#include"Inventory.h"
#include"platform\CCPlatformMacros.h"
#include<vector>

class Weapon:public Inventory
{
public:
	Weapon();
	~Weapon();
protected:
	CC_SYNTHESIZE(int, damage, Damage);
};

