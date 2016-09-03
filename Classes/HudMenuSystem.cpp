#include "HudMenuSystem.h"
#include "HudCursor.h"
#include "HudMenu.h"
#include "HudLayer.h"
#include "HudMenuItem.h"
#include "HudInventoryMenu.h"
#include "ToolFunction.h"
#include "cocos2d.h"



HudMenuSystem::HudMenuSystem()
{
}


HudMenuSystem::~HudMenuSystem()
{
}

void HudMenuSystem::init()
{
	windowSize = cocos2d::Director::getInstance()->getWinSize();

	initMainMenu();

	HudMenuItem* activeMenuItem = new HudMenuItem(ToolFunction::WStr2UTF8(L"活动"));
	mainMenu->addItem(activeMenuItem);

	initInventoryMenu();

	HudCursor::getInstance()->setCurMenu(mainMenu);
	hide();
}

void HudMenuSystem::update()
{

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

void HudMenuSystem::initMainMenu()
{
	mainMenu = new HudMenu(cocos2d::Rect(0, 0, 150, 400));
	HudLayer::getInstance()->addChild(mainMenu->getSprite(), 2);

	cocos2d::Point topLeft;
	topLeft.x = 50;
	topLeft.y = 50;

	cocos2d::Point position;
	position.x = mainMenu->getWidth() / 2+topLeft.x;
	position.y = windowSize.y-mainMenu->getHeight() / 2-topLeft.y;

	mainMenu->setPosition(position.x, position.y);
}

void HudMenuSystem::initInventoryMenu()
{
	HudMenuItem* inventoryMenuItem = new HudMenuItem(ToolFunction::WStr2UTF8(L"物品"));
	mainMenu->addItem(inventoryMenuItem);

	inventoryMenu = new HudInventoryMenu(cocos2d::Rect(0, 0, 300, 400));
	HudLayer::getInstance()->addChild(inventoryMenu->getSprite(), 2);

	int mainMenuWidth = mainMenu->getWidth();

	cocos2d::Point position;
	position.x = mainMenuWidth + inventoryMenu->getWidth() / 2 + 10+50;
	position.y = windowSize.y - inventoryMenu->getHeight() / 2 - 50;

	inventoryMenu->setPosition(position.x, position.y);
	inventoryMenu->setParent(mainMenu);

	inventoryMenuItem->setRelateMenu(inventoryMenu);
}
