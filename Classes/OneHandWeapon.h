#pragma once
#include "Weapon.h"

class OneHandWeapon :
	public Weapon
{
public:
	OneHandWeapon();
	virtual ~OneHandWeapon();
	OneHandWeapon* clone();
	void copyData(OneHandWeapon* inventory);
protected:

};

