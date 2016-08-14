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
	menu = new HudMenuItem(cocos2d::Rect(0, 0, 100, 500));
	HudLayer::getInstance()->addChild(menu->getSprite(),2);
	menu->setPosition(cocos2d::Point(100, 300));

	HudMenuItem* inventoryMenu = new HudMenuItem(cocos2d::Rect(100, 100, 100, 100));
	inventoryMenu->setName("inventory");
	menu->addChildItem(inventoryMenu);

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
