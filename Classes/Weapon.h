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
	void addSphere(const std::string& sphereID);
	WeaponSphereHandler* getSphereHandler();
	
protected:
	std::string getExtraDescription();
	CC_SYNTHESIZE(int, weaponDamage, WeaponDamage);
	WeaponSphereHandler* sphereHandler;
};
