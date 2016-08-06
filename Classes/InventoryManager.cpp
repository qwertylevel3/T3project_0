#include "InventoryManager.h"
#include"cocos2d.h"
#include"tinyxml2\tinyxml2.h"
#include<sstream>

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

		tinyxml2::XMLElement* nameElement = inventory->FirstChildElement("name");
		std::string name = nameElement->GetText();
		model->setName(name);

		tinyxml2::XMLElement* cnameElement = inventory->FirstChildElement("cname");
		std::string cname = cnameElement->GetText();
		std::wstring wcname(cname.length(), L' ');
		std::copy(cname.begin(), cname.end(), wcname.begin());
		model->setCname(wcname);

		tinyxml2::XMLElement* priceElement = inventory->FirstChildElement("price");
		std::stringstream priceStream(priceElement->GetText());
		int price;
		priceStream >> price;
		model->setPrice(price);

		tinyxml2::XMLElement* weightElement = inventory->FirstChildElement("weight");
		std::stringstream weightStream(weightElement->GetText());
		int weight;
		weightStream >> weight;
		model->setWeight(weight);

		tinyxml2::XMLElement* spriteNameElement = inventory->FirstChildElement("spriteName");
		std::string spriteName = spriteNameElement->GetText();
		model->setSpriteName(spriteName);

		inventoryMap[model->getName()] = model;

		inventory = inventory->NextSiblingElement();
	}

}

Inventory * InventoryManager::getInventory(std::string inventoryName)
{
	return inventoryMap[inventoryName]->makeInventory();
}
