#pragma once

#include"Inventory.h"

class InventoryMenuItem
{
public:
	InventoryMenuItem();
	~InventoryMenuItem();
protected:
	CC_SYNTHESIZE(Inventory*, inventory, Inventory);
	cocos2d::Label* itemLabel;
};

