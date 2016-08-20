#pragma once

#include"Inventory.h"
#include"Singleton.h"
#include"InventoryModel.h"
#include "tinyxml2/tinyxml2.h"

class InventoryManager:public Singleton<InventoryManager>
{
public:
	InventoryManager();
	~InventoryManager();
	void init();
	Inventory* getInventory(std::string inventoryName);
protected:
	std::string getInventoryStrAttr(tinyxml2::XMLElement* inventory, std::string attrName);
	std::wstring getInventoryWStrAttr(tinyxml2::XMLElement* inventory, std::string attrName);
	int getInventoryIntAttr(tinyxml2::XMLElement* inventory, std::string attrName);
	std::map<std::string, InventoryModel*> inventoryMap;
	tinyxml2::XMLElement* getChildElement(tinyxml2::XMLElement* parent, std::string name);

	tinyxml2::XMLElement* curInventoryElement;
};

