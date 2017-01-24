#pragma once

#include"Inventory.h"
#include"Singleton.h"
#include "XMLConfigure.h"
#include "tinyxml2/tinyxml2.h"
#include "Inventory.h"

class Weapon;
class Arrow;
class Supply;
class Armor;
class Accessory;
class Note;

class InventoryFactory:public XMLConfigure,public Singleton<InventoryFactory>
{
public:
	InventoryFactory();
	~InventoryFactory();
	void init();
	Inventory* getInventory(std::string inventoryName);
	std::string queryCname(const std::string& inventoryName);
	Inventory::Type queryInventoryType(const std::string& inventoryName);
	int queryInventoryWeight(const std::string& inventoryName);
	int queryInventoryLevel(const std::string& inventoryName);
	std::string getRandomInventory(int level);
	std::string getRandomNote();
protected:
	void initModel(tinyxml2::XMLElement* inventoryElement,const std::string& type);
	void initBaseData(tinyxml2::XMLElement* inventoryElement,Inventory* model);
	void initWeaponData(tinyxml2::XMLElement* inventoryElement, Weapon* weaponModel);
	void initArmorData(tinyxml2::XMLElement* inventoryElement, Armor* armorModel);
	void initAccessoryData(tinyxml2::XMLElement* inventoryElement, Accessory* accessoryModel);
	void initArrowData(tinyxml2::XMLElement* inventoryElement, Arrow* model);
	void initSupplyData(tinyxml2::XMLElement* inventoryElement, Supply* supplyModel);
	void initNoteData(tinyxml2::XMLElement* inventoryElement, Note* noteModel);

	std::map<std::string, Inventory*> inventoryMap;
	tinyxml2::XMLElement* curInventoryElement;

	std::vector<std::vector<std::string> > inventoryLevelBox;
	std::vector<std::string> noteBox;
};

