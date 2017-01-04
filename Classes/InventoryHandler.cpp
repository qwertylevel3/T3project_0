#include "InventoryHandler.h"
#include "InventoryFactory.h"
#include "StoreyInventoryHandler.h"
#include "Dungeon.h"

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

void InventoryHandler::addInventory(Inventory* inventory, int count)
{
	addInventory(inventory->getName(), count);
	delete inventory;
}

void InventoryHandler::removeInventory(std::string inventoryName, int count)
{
	if (inventoryBox.count(inventoryName))
	{
		if (inventoryBox[inventoryName] <= count)
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

int InventoryHandler::queryInventoryCountByName(const std::string& inventoryName)
{
	if (inventoryBox.count(inventoryName))
	{
		return inventoryBox[inventoryName];
	}
	return 0;
}

std::string InventoryHandler::queryInventoryNameByIndex(int index)
{
	std::map<std::string, int>::iterator iter = inventoryBox.begin();
	int count = 0;
	while (count!=index)
	{
		count++;
		iter++;
	}
	return iter->first;
}

void InventoryHandler::clear()
{
	inventoryBox.clear();
}

void InventoryHandler::drop(cocos2d::Point coord)
{
	std::map<std::string, int>::iterator iter = inventoryBox.begin();
	while (iter != inventoryBox.end())
	{
		Field::Storey* storey = Field::Dungeon::getInstance()->getStorey();
		for (int i = 0; i < iter->second; i++)
		{
			Inventory* inventory = InventoryFactory::getInstance()->getInventory(iter->first);
			storey->getInventoryHandler()->addInventory(inventory, coord.x, coord.y);
		}
		iter++;
	}
	clear();
}

int InventoryHandler::calculateSumWeight()
{
	int sumWeight = 0;
	std::map<std::string, int>::iterator iter = inventoryBox.begin();
	while (iter!=inventoryBox.end())
	{
		int weight = InventoryFactory::getInstance()->queryInventoryWeight(iter->first);
		sumWeight += weight*iter->second;
		iter++;
	}
	return sumWeight;
}
