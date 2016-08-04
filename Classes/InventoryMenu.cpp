#include "InventoryMenu.h"
#include"Inventory.h"
#include"Player.h"
#include"InventoryMenuItem.h"

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

	Character* player=Player::getInstance()->getcharacterPtr();
	std::vector<Inventory*> inventoryList = player->getInventoryList();

	for (int i = 0; i < inventoryList.size(); i++)
	{
		InventoryMenuItem* item = new InventoryMenuItem(inventoryList[i]);
		
		addItem(item,i);
	}
}

void InventoryMenu::hide()
{
	sprite->setVisible(false);

	sprite->removeAllChildren();
}

void InventoryMenu::addItem(InventoryMenuItem * item,int index)
{
	cocos2d::Label* label = item->getLable();

	label->setPosition(60,400-index*label->getLineHeight());

	sprite->addChild(label);
}
