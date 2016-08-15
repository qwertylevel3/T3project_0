#include "HudMenu.h"
#include"HudMenuItem.h"
#include"HudCursor.h"
#include"HudLayer.h"
#include<string>



HudMenu::HudMenu()
{
}


HudMenu::~HudMenu()
{
}

void HudMenu::init()
{
	menu = new HudMenuItem(cocos2d::Rect(0, 0, 100, 500));
	HudLayer::getInstance()->addChild(menu->getSprite(),2);
	menu->setPosition(cocos2d::Point(50, 550));

	HudMenuItem* inventoryMenu = new HudMenuItem(cocos2d::Rect(0, 0, 100, 100));
	inventoryMenu->setName(L"物品");
	menu->addChildItem(inventoryMenu);

	HudMenuItem* activeMenu = new HudMenuItem(cocos2d::Rect(0, 0, 100, 100));
	activeMenu->setName(L"行动");
	menu->addChildItem(activeMenu);


	//HudLayer::getInstance()->addChild(HudCursor::getInstance()->getSprite(),2);
	//HudCursor::getInstance()->hide();

	HudCursor::getInstance()->setCurItem(menu);
	hide();
}

void HudMenu::show()
{
	menu->show();
}

void HudMenu::hide()
{
	menu->hide();
}
