#include "HudMenuSystem.h"
#include "HudCursor.h"
#include "HudMenu.h"
#include "HudLayer.h"
#include "HudMenuItem.h"
#include "HudInventoryMenu.h"
#include "ToolFunction.h"



HudMenuSystem::HudMenuSystem()
{
}


HudMenuSystem::~HudMenuSystem()
{
}

void HudMenuSystem::init()
{
	mainMenu = new HudMenu(cocos2d::Rect(0, 0, 150, 500));
	HudLayer::getInstance()->addChild(mainMenu->getSprite(), 2);
	mainMenu->setPosition(150, 300);

	HudMenuItem* activeMenuItem = new HudMenuItem(ToolFunction::WStr2UTF8(L"活动"));
	mainMenu->addItem(activeMenuItem);

	HudMenuItem* inventoryMenuItem = new HudMenuItem(ToolFunction::WStr2UTF8(L"物品"));
	mainMenu->addItem(inventoryMenuItem);

	inventoryMenu = new HudInventoryMenu(cocos2d::Rect(0, 0, 300, 500));
	HudLayer::getInstance()->addChild(inventoryMenu->getSprite(), 2);
	inventoryMenu->setPosition(400, 300);
	inventoryMenuItem->setRelateMenu(inventoryMenu);

	HudCursor::getInstance()->setCurMenu(mainMenu);
	hide();
}

void HudMenuSystem::show()
{
	HudCursor::getInstance()->setCurMenu(mainMenu);
	HudCursor::getInstance()->show();
	mainMenu->show();
}

void HudMenuSystem::hide()
{
	HudCursor::getInstance()->hide();
	inventoryMenu->hide();
	mainMenu->hide();
}

void HudMenuSystem::handleKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode)
{
	HudCursor::getInstance()->handleKeyPressed(keyCode);
}
