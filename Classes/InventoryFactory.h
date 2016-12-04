#pragma once

#include"Inventory.h"
#include"Singleton.h"
#include "XMLConfigure.h"
#include "tinyxml2/tinyxml2.h"
#include "Inventory.h"

class Weapon;
class Arrow;
class Supply;

class InventoryFactory:public XMLConfigure,public Singleton<InventoryFactory>
{
public:
	InventoryFactory();
	~InventoryFactory();
	void init();
	Inventory* getInventory(std::string inventoryName);
	std::string getCname(const std::string& inventoryName);
	Inventory::Type getInventoryType(const std::string& inventoryName);
protected:
	void initModel(tinyxml2::XMLElement* inventoryElement,const std::string& type);
	void initBaseData(tinyxml2::XMLElement* inventoryElement,Inventory* model);
	void initWeaponData(tinyxml2::XMLElement* inventoryElement, Weapon* weaponModel);
	void initArrowData(tinyxml2::XMLElement* inventoryElement, Arrow* model);
	void initSupplyData(tinyxml2::XMLElement* inventoryElement, Supply* supplyModel);

	std::map<std::string, Inventory*> inventoryMap;
	tinyxml2::XMLElement* curInventoryElement;
};

