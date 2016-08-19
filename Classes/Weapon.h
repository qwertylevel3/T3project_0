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
	CC_SYNTHESIZE(int, weaponDamage, WeaponDamage);
	CC_SYNTHESIZE(int, strRequire, StrRequire);
	CC_SYNTHESIZE(int, agiRequire, AgiRequire);
	CC_SYNTHESIZE(int, intRequire, IntRequire);
};

