#include "InventoryManager.h"
#include"cocos2d.h"
#include<sstream>
#include "ToolFunction.h"

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
		InventoryModel* model = new InventoryModel();

		model->setType(getInventoryStrAttr(inventory,"type"));
		model->setName(getInventoryStrAttr(inventory,"name"));
		model->setCname(getInventoryWStrAttr(inventory,"cname"));
		model->setPrice(getInventoryIntAttr(inventory,"price"));
		model->setWeight(getInventoryIntAttr(inventory,"weight"));
		model->setSpriteName(getInventoryStrAttr(inventory,"spriteName"));

		model->setEvadeProAdd(getInventoryIntAttr(inventory,"evadeProAdd"));
		model->setAccuracyProAdd(getInventoryIntAttr(inventory, "accuracyProAdd"));
		model->setCriticalProAdd(getInventoryIntAttr(inventory, "criticalProAdd"));
		model->setCriticalAdd(getInventoryIntAttr(inventory, "criticalAdd"));
		model->setBlockProAdd(getInventoryIntAttr(inventory, "blockProAdd"));
		model->setBlockAdd(getInventoryIntAttr(inventory, "blockAdd"));
		model->setComboProAdd(getInventoryIntAttr(inventory, "comboProAdd"));

		inventoryMap[model->getName()] = model;

		inventory = inventory->NextSiblingElement();
	}

}

Inventory * InventoryManager::getInventory(std::string inventoryName)
{
	return inventoryMap[inventoryName]->makeInventory();
}


std::string InventoryManager::getInventoryStrAttr(tinyxml2::XMLElement* inventory, std::string attrName)
{
	tinyxml2::XMLElement* childElement = getChildElement(inventory, attrName);
	return childElement->GetText();
}

std::wstring InventoryManager::getInventoryWStrAttr(tinyxml2::XMLElement* inventory, std::string attrName)
{
	tinyxml2::XMLElement* childElement = getChildElement(inventory, attrName);
	return ToolFunction::string2wstring(childElement->GetText());
}

int InventoryManager::getInventoryIntAttr(tinyxml2::XMLElement* inventory, std::string attrName)
{
	tinyxml2::XMLElement* childElement = getChildElement(inventory, attrName);
	return ToolFunction::string2int(childElement->GetText());
}

tinyxml2::XMLElement* InventoryManager::getChildElement(tinyxml2::XMLElement* parent, std::string name)
{
	tinyxml2::XMLElement* element = parent->FirstChildElement(name.c_str());
	CCAssert(element, (std::string("unknow element type") + name).c_str());
	return element;
}
