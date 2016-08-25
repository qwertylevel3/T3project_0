#include "HudMenuSystem.h"
#include "HudCursor.h"
#include "HudMenu.h"
#include "HudLayer.h"
#include "HudMenuItem.h"



HudMenuSystem::HudMenuSystem()
{
}


HudMenuSystem::~HudMenuSystem()
{
}

void HudMenuSystem::init()
{
	menu = new HudMenu(cocos2d::Rect(0, 0, 150, 500));
	HudLayer::getInstance()->addChild(menu->getSprite(), 2);
	menu->setPosition(150, 300);

	HudMenuItem* activeMenuItem = new HudMenuItem(L"活动");
	menu->addItem(activeMenuItem);

	HudMenuItem* inventoryMenuItem = new HudMenuItem(L"物品");
	menu->addItem(inventoryMenuItem);

	HudCursor::getInstance()->setCurMenu(menu);
	hide();
}

void HudMenuSystem::show()
{
	HudCursor::getInstance()->show();
	menu->show();
}

void HudMenuSystem::hide()
{
	HudCursor::getInstance()->hide();
	menu->hide();
}

void HudMenuSystem::handleKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode)
{
	HudCursor::getInstance()->handleKeyPressed(keyCode);
}
