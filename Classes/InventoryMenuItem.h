#pragma once

#include"Inventory.h"

class InventoryMenuItem
{
public:
	InventoryMenuItem(Inventory* inv);
	~InventoryMenuItem();
	cocos2d::Label* getLable();
protected:
	Inventory* inventory;
	cocos2d::Label* itemLabel;
};

