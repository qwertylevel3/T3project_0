#pragma once

#include"Inventory.h"
#include"platform\CCPlatformMacros.h"
#include<vector>

class InventoryInHand:public Inventory
{
public:
	InventoryInHand();
	virtual ~InventoryInHand();
	void equipLeftHand(Character* character);
	void unequipLeftHand(Character* character);
	void equipRightHand(Character* character);
	void unequipRightHand(Character* character);
	void copyData(InventoryInHand* inventory);
protected:
	CC_SYNTHESIZE(int, strRequire, StrRequire);
	CC_SYNTHESIZE(int, agiRequire, AgiRequire);
	CC_SYNTHESIZE(int, intRequire, IntRequire);
};

