#include "InventoryHandler.h"
#include "InventoryManager.h"


InventoryHandler::InventoryHandler()
{
}


InventoryHandler::~InventoryHandler()
{
}

void InventoryHandler::addInventory(const std::string& inventoryName, int count)
{
	if (inventoryBox.count(inventoryName))
	{
		inventoryBox[inventoryName] = inventoryBox[inventoryName] + count;
	}
	else
	{
		inventoryBox[inventoryName] = count;
	}
}

void InventoryHandler::addInventory(Inventory* inventory)
{
	addInventory(inventory->getName(), 1);
	delete inventory;
}

void InventoryHandler::removeInventory(const std::string& inventoryName, int count)
{
	if (inventoryBox.count(inventoryName))
	{
		if (inventoryBox[inventoryName]<=count)
		{
			inventoryBox[inventoryName] = 0;
		}
		else
		{
			inventoryBox[inventoryName] = inventoryBox[inventoryName] - count;
		}
	}
}

std::map<std::string, int>& InventoryHandler::getAllInventory()
{
	return inventoryBox;
}

int InventoryHandler::getCount(const std::string& inventoryName)
{
	if (inventoryBox.count(inventoryName))
	{
		return inventoryBox[inventoryName];
	}
	return 0;
}

Inventory* InventoryHandler::getInventory(const std::string& inventoryName)
{
	if (inventoryBox.count(inventoryName) && inventoryBox[inventoryName]>0)
	{
		inventoryBox[inventoryName] = inventoryBox[inventoryName] - 1;
		return InventoryManager::getInstance()->getInventory(inventoryName);
	}
	return nullptr;
}
