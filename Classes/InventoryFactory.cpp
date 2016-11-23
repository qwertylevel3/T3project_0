#include "InventoryFactory.h"
#include"cocos2d.h"
#include<sstream>
#include "OneHandWeapon.h"
#include "TwoHandWeapon.h"
#include "Shield.h"
#include "ToolFunction.h"
#include "Accessory.h"
#include "Armor.h"
#include "Supply.h"
#include "Bow.h"
#include "Arrow.h"

USING_NS_CC;



InventoryFactory::InventoryFactory()
{
}


InventoryFactory::~InventoryFactory()
{
}

void InventoryFactory::init()
{
//	CCSpriteFrameCache::getInstance()->addSpriteFramesWithFile("weapon.plist");

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

Inventory * InventoryFactory::getInventory(std::string inventoryName)
{
	return inventoryMap[inventoryName]->clone();
}


std::string InventoryFactory::getCname(const std::string& inventoryName)
{
	return inventoryMap[inventoryName]->getCname();
}

Inventory::Type InventoryFactory::getInventoryType(const std::string& inventoryName)
{
	return inventoryMap[inventoryName]->getInventoryType();
}

void InventoryFactory::initModel(tinyxml2::XMLElement* inventoryElement, const std::string& type)
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
		TwoHandWeapon* model = new TwoHandWeapon();
		model->setInventoryType(Inventory::TwoHandWeapon);

		initBaseData(inventoryElement, model);
		initWeaponData(inventoryElement, model);

		inventoryMap[model->getName()] = model;
	}
	else if (type == "bow")
	{
		Bow* model = new Bow();
		model->setInventoryType(Inventory::Bow);

		initBaseData(inventoryElement, model);
		initWeaponData(inventoryElement, model);

		inventoryMap[model->getName()] = model;
	}
	else if (type=="arrow")
	{
		Arrow* model = new Arrow();
		initBaseData(inventoryElement, model);
		initArrowData(inventoryElement, model);

		inventoryMap[model->getName()] = model;
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

void InventoryFactory::initBaseData(tinyxml2::XMLElement* inventoryElement,Inventory* model)
{
	model->setName(getChildElementStrAttr(inventoryElement, "name"));
	model->setCname(getChildElementStrAttr(inventoryElement, "cname"));
	model->setLevel(getChildElementIntAttr(inventoryElement, "level"));
	model->setPrice(getChildElementIntAttr(inventoryElement, "price"));
	model->setWeight(getChildElementIntAttr(inventoryElement, "weight"));
	model->setSpriteName(getChildElementStrAttr(inventoryElement, "spriteName"));

	tinyxml2::XMLElement* buffBoxElement = getChildElement(inventoryElement, "buffBox");
	tinyxml2::XMLElement* buffElement = getChildElement(buffBoxElement, "buffID");
	while (buffElement)
	{
		model->addBuff(buffElement->GetText());
		buffElement = buffElement->NextSiblingElement();
	}
}

void InventoryFactory::initWeaponData(tinyxml2::XMLElement* inventoryElement, Weapon* weaponModel)
{
	weaponModel->setWeaponDamage(getChildElementIntAttr(inventoryElement, "weaponDamage"));
	weaponModel->setStrRequire(getChildElementIntAttr(inventoryElement, "strRequire"));
	weaponModel->setAgiRequire(getChildElementIntAttr(inventoryElement, "agiRequire"));
	weaponModel->setIntRequire(getChildElementIntAttr(inventoryElement, "intRequire"));

	tinyxml2::XMLElement* sphereBoxElement = getChildElement(inventoryElement, "sphereBox");
	tinyxml2::XMLElement* sphereElement = getChildElement(sphereBoxElement, "sphereID");
	while (sphereElement)
	{
		weaponModel->addSphere(sphereElement->GetText());
		sphereElement = sphereElement->NextSiblingElement();
	}
}

void InventoryFactory::initArrowData(tinyxml2::XMLElement* inventoryElement, Arrow* model)
{
	model->setDamage(getChildElementIntAttr(inventoryElement, "damage"));
}
