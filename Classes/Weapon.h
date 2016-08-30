#pragma once

#include "InventoryInHand.h"
#include "WeaponAtkArea.h"


class Weapon :
	public InventoryInHand
{
public:
	Weapon();
	virtual ~Weapon();
	void copyData(Weapon* inventory);
	void addAtkAreaPoint(cocos2d::Point point);
	std::vector<cocos2d::Point> getAtkArea(Character* attacker);
	WeaponAtkArea* getAtkAreaPtr();
protected:
	CC_SYNTHESIZE(int, weaponDamage, WeaponDamage);
	WeaponAtkArea* atkArea;
};

