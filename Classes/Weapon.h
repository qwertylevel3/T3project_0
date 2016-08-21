#pragma once

#include"Inventory.h"
#include"platform\CCPlatformMacros.h"
#include<vector>

class Weapon:public Inventory
{
public:
	Weapon();
	~Weapon();
	void equipLeftHand(Character* character);
	void unequipLeftHand(Character* character);
	void equipRightHand(Character* character);
	void unequipRightHand(Character* character);
	Weapon* clone();
protected:
	CC_SYNTHESIZE(int, weaponDamage, WeaponDamage);
	CC_SYNTHESIZE(int, strRequire, StrRequire);
	CC_SYNTHESIZE(int, agiRequire, AgiRequire);
	CC_SYNTHESIZE(int, intRequire, IntRequire);
};

