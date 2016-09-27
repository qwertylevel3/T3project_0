#pragma once

#include <map>
#include <string>

class Inventory;

class InventoryHandler
{
public:
	InventoryHandler();
	~InventoryHandler();
	void addInventory(const std::string& inventoryName,int count);
	//************************************
	// Method:    addInventory
	// FullName:  InventoryHandler::addInventory
	// Access:    public 
	// Returns:   void
	// Qualifier: 会销毁 inventory 指针
	// Parameter: Inventory * inventory
	//************************************
	void addInventory(Inventory* inventory);
	void removeInventory(std::string inventoryName, int count);
	std::map<std::string, int>& getAllInventory();
	int getCount(const std::string& inventoryName);
	Inventory* getInventory(std::string inventoryName);
	Inventory* getInventory(int index);
protected:
	//记录每种inventory的个数
	std::map<std::string, int> inventoryBox;
};

