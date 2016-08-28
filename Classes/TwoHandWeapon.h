#pragma once
#include "Weapon.h"

class TwoHandWeapon :
	public Weapon
{
public:
	TwoHandWeapon();
	virtual ~TwoHandWeapon();
	void equipLeftHand(Character* character);
	void unequipLeftHand(Character* character);
	void equipRightHand(Character* character);
	void unequipRightHand(Character* character);
	TwoHandWeapon* clone();
	void copyData(TwoHandWeapon* inventory);
protected:
};

