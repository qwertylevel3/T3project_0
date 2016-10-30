#include "Inventory.h"
#include"cocos2d.h"
#include "InventoryBuffHandler.h"

USING_NS_CC;

Inventory::Inventory()
{
	icon = nullptr;
	inventoryBuffHandler = new InventoryBuffHandler();
}

Inventory::~Inventory()
{
	delete inventoryBuffHandler;
}

void Inventory::equipLeftHand(Character* character)
{
}

void Inventory::unequipLeftHand(Character* character)
{
}

void Inventory::equipRightHand(Character* character)
{
}

void Inventory::unequipRightHand(Character* character)
{
}

void Inventory::equipArmor(Character* character)
{
}

void Inventory::equipAccessory(Character* character)
{
}

void Inventory::load(Character* character)
{
}

void Inventory::unload(Character* character)
{
}

void Inventory::use(Character* character)
{
}

void Inventory::copyData(Inventory* inventory)
{
	inventory->setName(name);
	inventory->setCname(cname);
	inventory->setLevel(level);
	inventory->setPrice(price);
	inventory->setWeight(weight);
	inventory->setSpriteName(spriteName);
	inventory->setInventoryType(inventoryType);

	for each (std::string buffID in inventoryBuffHandler->getBuffIDBox())
	{
		inventory->addBuff(buffID);
	}
}

cocos2d::Sprite* Inventory::getIcon()
{
	CCAssert(!spriteName.empty(), std::string(name + " sprite name is empty").c_str());
	if (!icon)
	{
		icon = CCSprite::createWithSpriteFrameName(spriteName);
	}
	return icon;
}

void Inventory::addBuff(std::string buffID)
{
	inventoryBuffHandler->addBuff(buffID);
}

std::vector<std::string> Inventory::getAllInventoryBuff()
{
	return inventoryBuffHandler->getBuffIDBox();
}
