#include "InventoryHandler.h"
#include "InventoryFactory.h"


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

void InventoryHandler::addInventory(Inventory* inventory,int count)
{
	addInventory(inventory->getName(), count);
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

void InventoryHandler::removeInventory(int index, int count)
{
	int iterCount = 0;
	std::map<std::string, int>::iterator iter = inventoryBox.begin();
	while (iter != inventoryBox.end())
	{
		if (iterCount == index)
		{
			removeInventory(iter->first, count);
			return;
		}
		iterCount++;
		iter++;
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
		return InventoryFactory::getInstance()->getInventory(inventoryName);
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
