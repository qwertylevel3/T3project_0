#pragma once

#include"platform\CCPlatformMacros.h"
#include<string>
#include"Inventory.h"

class InventoryModel
{
public:
	InventoryModel();
	~InventoryModel();
	Inventory* makeInventory();
protected:
	CC_SYNTHESIZE(std::string, name, Name);
	CC_SYNTHESIZE(std::wstring, cname, Cname);
	CC_SYNTHESIZE(int, price, Price);
	CC_SYNTHESIZE(int, weight, Weight);
	CC_SYNTHESIZE(std::string, spriteName, SpriteName);
};

