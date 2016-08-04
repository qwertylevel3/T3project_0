#include "InventoryMenuItem.h"


InventoryMenuItem::InventoryMenuItem(Inventory* inv)
{
	inventory = inv;
	itemLabel = cocos2d::Label::createWithTTF(inventory->getName(), "fonts/arial.ttf", 24);
	itemLabel->retain();
}


InventoryMenuItem::~InventoryMenuItem()
{
	itemLabel->release();
}

cocos2d::Label * InventoryMenuItem::getLable()
{
	return itemLabel;
}
