#pragma once

#include"Inventory.h"
#include"platform\CCPlatformMacros.h"
#include"WeaponType.h"
#include"WeaponAdj.h"
#include<vector>

class Weapon:public Inventory
{
public:
	Weapon();
	~Weapon();
protected:
	CC_SYNTHESIZE(WeaponType*, type, Type);
	std::vector<WeaponAdj*> adjList;

	CC_SYNTHESIZE(int, damage, Damage);
};

