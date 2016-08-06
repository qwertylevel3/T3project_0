#pragma once

#include"Inventory.h"
#include"Singleton.h"
#include"InventoryModel.h"

class InventoryManager:public Singleton<InventoryManager>
{
public:
	InventoryManager();
	~InventoryManager();
	void init();
	Inventory* getInventory(std::string inventoryName);
protected:
	std::map<std::string, InventoryModel*> inventoryMap;
};

