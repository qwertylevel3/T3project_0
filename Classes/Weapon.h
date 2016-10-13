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
protected:
	CC_SYNTHESIZE(int, weaponDamage, WeaponDamage);
};

