#include "InventoryFactory.h"
#include "RandomNumber.h"
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
#include "Note.h"

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

	for (int i = 0; i <= 9; i++)
	{
		std::vector<std::string> tempBox;
		inventoryLevelBox.push_back(tempBox);
	}


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


std::string InventoryFactory::queryCname(const std::string& inventoryName)
{
	return inventoryMap[inventoryName]->getCname();
}

Inventory::Type InventoryFactory::queryInventoryType(const std::string& inventoryName)
{
	return inventoryMap[inventoryName]->getInventoryType();
}

int InventoryFactory::queryInventoryWeight(const std::string& inventoryName)
{
	return inventoryMap[inventoryName]->getWeight();
}

int InventoryFactory::queryInventoryLevel(const std::string& inventoryName)
{
	return inventoryMap[inventoryName]->getLevel();
}

std::string InventoryFactory::getRandomInventory(int level)
{
	int size = inventoryLevelBox[level].size();

	int roll = RandomNumber::getInstance()->randomInt(0, size - 1);

	return inventoryLevelBox[level][roll];
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
		Armor* model = new Armor();
		model->setInventoryType(Inventory::Armor);

		initBaseData(inventoryElement, model);
		initArmorData(inventoryElement, model);

		inventoryMap[model->getName()] = model;
	}
	else if (type == "accessory")
	{

		Accessory* model = new Accessory();
		model->setInventoryType(Inventory::Accessory);

		initBaseData(inventoryElement, model);
		initAccessoryData(inventoryElement, model);

		inventoryMap[model->getName()] = model;
	}
	else if (type == "supply")
	{
		Supply* model = new Supply();
		model->setInventoryType(Inventory::Supply);

		initBaseData(inventoryElement, model);
		initSupplyData(inventoryElement, model);

		inventoryMap[model->getName()] = model;
	}
	else if (type=="note")
	{
		Note* model = new Note();
		model->setInventoryType(Inventory::Note);

		initBaseData(inventoryElement, model);
		initNoteData(inventoryElement, model);

		inventoryMap[model->getName()] = model;
	}
	else
	{
		CCAssert(false, (std::string("unknow element type ") + type).c_str());
	}
}

void InventoryFactory::initBaseData(tinyxml2::XMLElement* inventoryElement,Inventory* model)
{
	std::string name = getChildElementStrAttr(inventoryElement, "name");
	model->setName(name);

	model->setCname(getChildElementStrAttr(inventoryElement, "cname"));
	model->setTips(getChildElementStrAttr(inventoryElement, "tips"));

	//////////////////////////////////////////////////////////////////////////

	int level = getChildElementIntAttr(inventoryElement, "level");
	model->setLevel(level);

	inventoryLevelBox[level].push_back(name);

	//////////////////////////////////////////////////////////////////////////

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

void InventoryFactory::initArmorData(tinyxml2::XMLElement* inventoryElement, Armor* armorModel)
{
	armorModel->setArmorCount(getChildElementIntAttr(inventoryElement, "armorCount"));

}

void InventoryFactory::initAccessoryData(tinyxml2::XMLElement* inventoryElement, Accessory* accessoryModel)
{

}

void InventoryFactory::initArrowData(tinyxml2::XMLElement* inventoryElement, Arrow* model)
{
	model->setDamage(getChildElementIntAttr(inventoryElement, "damage"));
}

void InventoryFactory::initSupplyData(tinyxml2::XMLElement* inventoryElement, Supply* supplyModel)
{
	supplyModel->setStrRequire(getChildElementIntAttr(inventoryElement, "strRequire"));
	supplyModel->setAgiRequire(getChildElementIntAttr(inventoryElement, "agiRequire"));
	supplyModel->setIntRequire(getChildElementIntAttr(inventoryElement, "intRequire"));
	supplyModel->setSkillName(getChildElementStrAttr(inventoryElement, "skillName"));
	supplyModel->setSupplyType(getChildElementIntAttr(inventoryElement, "supplyType"));

}

void InventoryFactory::initNoteData(tinyxml2::XMLElement* inventoryElement, Note* noteModel)
{
	noteModel->setTextID(getChildElementStrAttr(inventoryElement, "noteID"));
}
