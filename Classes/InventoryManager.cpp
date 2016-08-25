#include "InventoryManager.h"
#include"cocos2d.h"
#include<sstream>
#include "ToolFunction.h"
#include "Weapon.h"
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
		std::string type = getInventoryStrAttr(inventory, "type");

		initModel(inventory, type);

		inventory = inventory->NextSiblingElement();
	}
}

Inventory * InventoryManager::getInventory(std::string inventoryName)
{
	return inventoryMap[inventoryName]->clone();
}


void InventoryManager::initModel(tinyxml2::XMLElement* inventoryElement,const std::string& type)
{
	if (type == "weapon")
	{
		Weapon* model = new Weapon();
		model->setInventoryType(Inventory::Weapon);

		initBaseData(inventoryElement, model);
		initWeaponData(inventoryElement, model);

		inventoryMap[model->getName()] = model;
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
	model->setName(getInventoryStrAttr(inventoryElement, "name"));
	model->setCname(getInventoryStrAttr(inventoryElement, "cname"));
	model->setPrice(getInventoryIntAttr(inventoryElement, "price"));
	model->setWeight(getInventoryIntAttr(inventoryElement, "weight"));
	model->setSpriteName(getInventoryStrAttr(inventoryElement, "spriteName"));

	model->setEvadeProAdd(getInventoryIntAttr(inventoryElement, "evadeProAdd"));
	model->setAccuracyProAdd(getInventoryIntAttr(inventoryElement, "accuracyProAdd"));
	model->setCriticalProAdd(getInventoryIntAttr(inventoryElement, "criticalProAdd"));
	model->setCriticalAdd(getInventoryIntAttr(inventoryElement, "criticalAdd"));
	model->setBlockProAdd(getInventoryIntAttr(inventoryElement, "blockProAdd"));
	model->setBlockAdd(getInventoryIntAttr(inventoryElement, "blockAdd"));
	model->setComboProAdd(getInventoryIntAttr(inventoryElement, "comboProAdd"));
}

void InventoryManager::initWeaponData(tinyxml2::XMLElement* inventoryElement, Weapon* weaponModel)
{
	weaponModel->setWeaponDamage(getInventoryIntAttr(inventoryElement, "weaponDamage"));
	weaponModel->setStrRequire(getInventoryIntAttr(inventoryElement, "strRequire"));
	weaponModel->setAgiRequire(getInventoryIntAttr(inventoryElement, "agiRequire"));
	weaponModel->setIntRequire(getInventoryIntAttr(inventoryElement, "intRequire"));
}

std::string InventoryManager::getInventoryStrAttr(tinyxml2::XMLElement* inventoryElement, std::string attrName)
{
	tinyxml2::XMLElement* childElement = getChildElement(inventoryElement, attrName);
	return childElement->GetText();
}

std::wstring InventoryManager::getInventoryWStrAttr(tinyxml2::XMLElement* inventoryElement, std::string attrName)
{
	tinyxml2::XMLElement* childElement = getChildElement(inventoryElement, attrName);
	std::string temp=childElement->GetText();
	return ToolFunction::string2wstring(childElement->GetText());
}

int InventoryManager::getInventoryIntAttr(tinyxml2::XMLElement* inventoryElement, std::string attrName)
{
	tinyxml2::XMLElement* childElement = getChildElement(inventoryElement, attrName);
	return ToolFunction::string2int(childElement->GetText());
}

tinyxml2::XMLElement* InventoryManager::getChildElement(tinyxml2::XMLElement* parent, std::string name)
{
	tinyxml2::XMLElement* element = parent->FirstChildElement(name.c_str());
	CCAssert(element, (std::string("unknow element type ") + name).c_str());
	return element;
}
