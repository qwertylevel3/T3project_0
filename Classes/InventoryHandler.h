#pragma once

#include <map>
#include <string>
#include "base/ccTypes.h"

class Inventory;

class InventoryHandler
{
public:
	InventoryHandler();
	~InventoryHandler();
	void addInventory(const std::string& inventoryName,int count=1);
	//************************************
	// Method:    addInventory
	// FullName:  InventoryHandler::addInventory
	// Access:    public 
	// Returns:   void
	// Qualifier: 会销毁 inventory 指针
	// Parameter: Inventory * inventory
	//************************************
	void addInventory(Inventory* inventory,int count=1);
	void removeInventory(std::string inventoryName, int count);
	void removeInventory(int index, int count);
	std::map<std::string, int>& getAllInventory();
	int getCount(const std::string& inventoryName);
	Inventory* getInventory(std::string inventoryName);
	Inventory* getInventory(int index);

	void clear();

	//计算总重量
	int calculateSumWeight();



	//************************************
	// Method:    drop
	// FullName:  InventoryHandler::drop
	// Access:    public 
	// Returns:   void
	// Qualifier: character死亡时调用，将当前所有物品丢弃到地面
	//************************************
	void drop(cocos2d::Point coord);
protected:
	//记录每种inventory的个数
	std::map<std::string, int> inventoryBox;


};

