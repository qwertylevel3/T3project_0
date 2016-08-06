#include "InventoryModel.h"
#include"cocos2d.h"

USING_NS_CC;



InventoryModel::InventoryModel()
{
}


InventoryModel::~InventoryModel()
{
}

Inventory * InventoryModel::makeInventory()
{
	Inventory* inv = new Inventory();

	inv->setName(name);
	inv->setCname(cname);
	inv->setPrice(price);
	inv->setWeight(weight);
	inv->setIcon(CCSprite::createWithSpriteFrameName(spriteName));

	return inv;
}
