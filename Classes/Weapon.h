#pragma once

#include "InventoryInHand.h"

class WeaponSphereHandler;

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
