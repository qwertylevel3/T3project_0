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

void InventoryHandler::removeInventory(std::string inventoryName, int count)
{
	if (inventoryBox.count(inventoryName))
	{
		if (inventoryBox[inventoryName]<=count)
		{
			inventoryBox[inventoryName] = 0;
			inventoryBox.erase(inventoryName);
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

Inventory* InventoryHandler::getInventory(std::string inventoryName)
{
	if (inventoryBox.count(inventoryName) && inventoryBox[inventoryName]>0)
	{
		removeInventory(inventoryName, 1);
		return InventoryManager::getInstance()->getInventory(inventoryName);
	}
	return nullptr;
}

Inventory* InventoryHandler::getInventory(int index)
{
	int count = 0;
	std::map<std::string, int>::const_iterator iter = inventoryBox.cbegin();
	while (count != index)
	{
		iter++;
		count++;
	}
	return getInventory(iter->first);
}
