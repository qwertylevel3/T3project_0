#include "Inventory.h"
#include"cocos2d.h"

USING_NS_CC;


Inventory::Inventory()
{
	evadeProAdd = 0;
	accuracyProAdd = 0;
	criticalProAdd = 0;
	criticalAdd = 0;
	blockProAdd = 0;
	blockAdd = 0;
	comboProAdd = 0;

	icon = nullptr;
}


Inventory::~Inventory()
{
}

void Inventory::equip(Character* character)
{
}

void Inventory::unequip(Character* character)
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
	inventory->setPrice(price);
	inventory->setWeight(weight);
	inventory->setSpriteName(spriteName);
	inventory->setInventoryType(inventoryType);

	inventory->setEvadeProAdd(evadeProAdd);
	inventory->setAccuracyProAdd(accuracyProAdd);
	inventory->setCriticalProAdd(criticalProAdd);
	inventory->setCriticalAdd(criticalAdd);
	inventory->setBlockProAdd(blockProAdd);
	inventory->setBlockAdd(blockAdd);
	inventory->setComboProAdd(comboProAdd);
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
