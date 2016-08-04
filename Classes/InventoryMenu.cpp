#include "InventoryMenu.h"

USING_NS_CC;

void InventoryMenu::init()
{
	CCSpriteFrameCache::getInstance()->addSpriteFramesWithFile("InventoryMenu.plist");
	sprite = CCSprite::createWithSpriteFrameName("InventoryMenu.png");
	sprite->retain();
	sprite->setPosition(250, 350);

	hide();
}

InventoryMenu::InventoryMenu()
{
}


InventoryMenu::~InventoryMenu()
{
	sprite->release();
}

void InventoryMenu::show()
{
	sprite->setVisible(true);
}

void InventoryMenu::hide()
{
	sprite->setVisible(false);
}
