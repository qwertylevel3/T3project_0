#pragma once

#include"Inventory.h"
#include"Singleton.h"
#include "tinyxml2/tinyxml2.h"

class Weapon;

class InventoryManager:public Singleton<InventoryManager>
{
public:
	InventoryManager();
	~InventoryManager();
	void init();
	Inventory* getInventory(std::string inventoryName);
protected:
	void initModel(tinyxml2::XMLElement* inventoryElement,const std::string& type);
	void initBaseData(tinyxml2::XMLElement* inventoryElement,Inventory* model);
	void initWeaponData(tinyxml2::XMLElement* inventoryElement, Weapon* weaponModel);

	std::string getChildElementStrAttr(tinyxml2::XMLElement* element, std::string attrName);
	std::wstring getChildElementWStrAttr(tinyxml2::XMLElement* element, std::string attrName);
	int getChildElementIntAttr(tinyxml2::XMLElement* element, std::string attrName);

	tinyxml2::XMLElement* getChildElement(tinyxml2::XMLElement* parent, std::string name);

	std::map<std::string, Inventory*> inventoryMap;
	tinyxml2::XMLElement* curInventoryElement;
};

