#include "InventoryManager.h"
#include"cocos2d.h"
#include<sstream>
#include "OneHandWeapon.h"
#include "TwoHandWeapon.h"
#include "Shield.h"
#include "ToolFunction.h"
#include "Accessory.h"
#include "Armor.h"
#include "Supply.h"

USING_NS_CC;



InventoryManager::InventoryManager()
{
}


InventoryManager::~InventoryManager()
{
}

void InventoryManager::init()
{
	CCSpriteFrameCache::getInstance()->addSpriteFramesWithFile("weapon.plist");

	tinyxml2::XMLDocument doc;
	doc.LoadFile("inventory.xml");
	tinyxml2::XMLElement* inventoryList = doc.RootElement();
	tinyxml2::XMLElement* inventory = inventoryList->FirstChildElement();
	while (inventory)
	{
		std::string type = getChildElementStrAttr(inventory, "type");

		initModel(inventory, type);

		inventory = inventory->NextSiblingElement();
	}
}

Inventory * InventoryManager::getInventory(std::string inventoryName)
{
	return inventoryMap[inventoryName]->clone();
}


std::string InventoryManager::getCname(const std::string& inventoryName)
{
	return inventoryMap[inventoryName]->getCname();
}

Inventory::Type InventoryManager::getInventoryType(const std::string& inventoryName)
{
	return inventoryMap[inventoryName]->getInventoryType();
}

void InventoryManager::initModel(tinyxml2::XMLElement* inventoryElement, const std::string& type)
{
	if (type == "oneHandWeapon")
	{
		OneHandWeapon* model = new OneHandWeapon();
		model->setInventoryType(Inventory::OneHandWeapon);

		initBaseData(inventoryElement, model);
		initWeaponData(inventoryElement, model);

		inventoryMap[model->getName()] = model;
	}
	else if (type == "twoHandWeapon")
	{
	}
	else if (type == "shield")
	{

	}
	else if (type == "armor")
	{

	}
	else if (type == "accessory")
	{

	}
	else if (type == "supply")
	{

	}
	else
	{
		CCAssert(false, (std::string("unknow element type ") + type).c_str());
	}
}

void InventoryManager::initBaseData(tinyxml2::XMLElement* inventoryElement,Inventory* model)
{
	model->setName(getChildElementStrAttr(inventoryElement, "name"));
	model->setCname(getChildElementStrAttr(inventoryElement, "cname"));
	model->setLevel(getChildElementIntAttr(inventoryElement, "level"));
	model->setPrice(getChildElementIntAttr(inventoryElement, "price"));
	model->setWeight(getChildElementIntAttr(inventoryElement, "weight"));
	model->setSpriteName(getChildElementStrAttr(inventoryElement, "spriteName"));

	model->setEvadeProAdd(getChildElementIntAttr(inventoryElement, "evadeProAdd"));
	model->setAccuracyProAdd(getChildElementIntAttr(inventoryElement, "accuracyProAdd"));
	model->setCriticalProAdd(getChildElementIntAttr(inventoryElement, "criticalProAdd"));
	model->setCriticalAdd(getChildElementIntAttr(inventoryElement, "criticalAdd"));
	model->setBlockProAdd(getChildElementIntAttr(inventoryElement, "blockProAdd"));
	model->setBlockAdd(getChildElementIntAttr(inventoryElement, "blockAdd"));
	model->setComboProAdd(getChildElementIntAttr(inventoryElement, "comboProAdd"));
}

void InventoryManager::initWeaponData(tinyxml2::XMLElement* inventoryElement, Weapon* weaponModel)
{
	weaponModel->setWeaponDamage(getChildElementIntAttr(inventoryElement, "weaponDamage"));
	weaponModel->setStrRequire(getChildElementIntAttr(inventoryElement, "strRequire"));
	weaponModel->setAgiRequire(getChildElementIntAttr(inventoryElement, "agiRequire"));
	weaponModel->setIntRequire(getChildElementIntAttr(inventoryElement, "intRequire"));
}
