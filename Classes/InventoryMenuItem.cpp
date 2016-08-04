#include "InventoryMenuItem.h"


InventoryMenuItem::InventoryMenuItem()
{
	itemLabel = cocos2d::Label::createWithTTF(inventory->getName(), "fonts/arial.ttf", 24);
	itemLabel->retain();
}


InventoryMenuItem::~InventoryMenuItem()
{
	itemLabel->release();
}
