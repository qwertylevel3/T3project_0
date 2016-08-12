#pragma once

#include"Inventory.h"
#include"platform\CCPlatformMacros.h"
#include<vector>

class Weapon:public Inventory
{
public:
	Weapon();
	~Weapon();
	void equip(Character* character);
	void unequip(Character* character);
protected:
	CC_SYNTHESIZE(int, damage, Damage);
};

