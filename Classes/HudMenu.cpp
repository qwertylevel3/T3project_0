#include "HudMenu.h"
#include"HudMenuItem.h"
#include"HudCursor.h"
#include"HudLayer.h"



HudMenu::HudMenu()
{
}


HudMenu::~HudMenu()
{
}

void HudMenu::init()
{
	menu = new HudMenuItem(cocos2d::Rect(0, 0, 150, 500));
	HudLayer::getInstance()->addChild(menu->getSprite(),2);
	menu->setPosition(cocos2d::Point(50, 550));

	HudMenuItem* inventoryMenu = new HudMenuItem(cocos2d::Rect(100, 100, 100, 100));
	inventoryMenu->setName("inventory");
	menu->addChildItem(inventoryMenu);

	HudMenuItem* activeMenu = new HudMenuItem(cocos2d::Rect(100, 100, 100, 100));
	activeMenu->setName("active");
	menu->addChildItem(activeMenu);

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
