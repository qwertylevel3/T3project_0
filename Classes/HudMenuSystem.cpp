#include "HudMenuSystem.h"
#include "HudCursor.h"
#include "HudMenu.h"
#include "HudLayer.h"
#include "HudMenuItem.h"
#include "HudInventoryMenu.h"
#include "HudEquipMenu.h"
#include "ToolFunction.h"
#include "HudTrigActChildMenu.h"
#include "cocos2d.h"
#include "HudLayout.h"



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
	initActiveMenu();
	initInventoryMenu();
	initEquipMenu();

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
	equipMenu->hide();
	mainMenu->hide();
}

void HudMenuSystem::handleKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode)
{
	HudCursor::getInstance()->handleKeyPressed(keyCode);
}

void HudMenuSystem::initMainMenu()
{
	cocos2d::Size mainMenuSize = HudLayout::getInstance()->getmainMenuSize();
	cocos2d::Point mainMenuPosition = HudLayout::getInstance()->getMainMenuPosition();

	mainMenu = new HudMenu(cocos2d::Rect(0, 0, mainMenuSize.width, mainMenuSize.height));
	mainMenu->setPosition(mainMenuPosition.x, mainMenuPosition.y);
}

void HudMenuSystem::initInventoryMenu()
{
	HudMenuItem* inventoryMenuItem = new HudMenuItem(ToolFunction::WStr2UTF8(L"物品"));
	mainMenu->addItem(inventoryMenuItem);
	
	cocos2d::Size inventoryMenuSize = HudLayout::getInstance()->getMediumMenuSize();
	cocos2d::Point inventoryMenuPosition = HudLayout::getInstance()->getMediumMenuPosition();

	inventoryMenu = new HudInventoryMenu(cocos2d::Rect(0, 0, inventoryMenuSize.width, inventoryMenuSize.height));

	inventoryMenu->setPosition(inventoryMenuPosition.x, inventoryMenuPosition.y);
	inventoryMenu->setParent(mainMenu);

	HudTrigActChildMenu* trigger = new HudTrigActChildMenu(inventoryMenu);
	inventoryMenuItem->setTrigger(trigger);
}

void HudMenuSystem::initActiveMenu()
{
	HudMenuItem* activeMenuItem = new HudMenuItem(ToolFunction::WStr2UTF8(L"活动"));
	mainMenu->addItem(activeMenuItem);

}

void HudMenuSystem::initEquipMenu()
{
	HudMenuItem* equipMenuItem = new HudMenuItem(ToolFunction::WStr2UTF8(L"装备"));
	mainMenu->addItem(equipMenuItem);

	cocos2d::Size equipMenuSize = HudLayout::getInstance()->getMediumMenuSize();
	cocos2d::Point equipMenuPosition = HudLayout::getInstance()->getMediumMenuPosition();

	equipMenu = new HudEquipMenu(cocos2d::Rect(0, 0, equipMenuSize.width, equipMenuSize.height));

	equipMenu->setPosition(equipMenuPosition.x, equipMenuPosition.y);
	equipMenu->setParent(mainMenu);

	HudTrigActChildMenu* trigger = new HudTrigActChildMenu(equipMenu);
	equipMenuItem->setTrigger(trigger);
}
