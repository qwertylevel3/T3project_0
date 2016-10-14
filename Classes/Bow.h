#pragma once

#include "Weapon.h"

class Bow:public Weapon
{
public:
	Bow();
	~Bow();
	void equipLeftHand(Character* character);
	void unequipLeftHand(Character* character);
	void equipRightHand(Character* character);
	void unequipRightHand(Character* character);
	Bow* clone();
	void copyData(Bow* inventory);
protected:
};

