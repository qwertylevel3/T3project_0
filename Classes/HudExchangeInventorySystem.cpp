#include "HudExchangeInventorySystem.h"
#include "KeyController.h"
#include "HudTrigGiveInv.h"
#include "HudCursor.h"
#include "HudMenuItem.h"
#include "InventoryFactory.h"
#include "ToolFunction.h"
#include "InventoryHandler.h"
#include "Player.h"
#include "HudMenu.h"

HudExchangeInventoryMenu::HudExchangeInventoryMenu()
	:HudMenu(cocos2d::Rect(0, 0, 300, 375))
{
	characterPtr = nullptr;
}

HudExchangeInventoryMenu::~HudExchangeInventoryMenu()
{
}

void HudExchangeInventoryMenu::update()
{
	clear();
	if (!characterPtr)
	{
		HudMenuItem* emptyItem = new HudMenuItem("empty");
		this->addItem(emptyItem);
		return;
	}

	InventoryHandler* inventoryHandler = characterPtr->getInventoryHandler();

	std::map<std::string, int> inventoryMap = inventoryHandler->getAllInventory();

	std::map<std::string, int>::const_iterator iter = inventoryMap.cbegin();
	while (iter != inventoryMap.cend())
	{
		std::string cname = InventoryFactory::getInstance()->queryCname(iter->first);
		std::string count = ToolFunction::int2string(iter->second);

		HudMenuItem* inventoryItem = new HudMenuItem(cname + " x" + count);

		setItemTrigger(inventoryItem);
		this->addItem(inventoryItem);

		iter++;
	}
	if (itemList.empty())
	{
		HudMenuItem* emptyItem = new HudMenuItem("empty");
		this->addItem(emptyItem);
	}
	HudCursor::getInstance()->setCurMenu(this);
}

void HudExchangeInventoryMenu::setCharacter(Character* character)
{
	characterPtr = character;
}


void HudExchangeInventoryMenu::setItemTrigger(HudMenuItem* item)
{
	HudTrigGiveInv* trigger = new HudTrigGiveInv();
	item->setTrigger(trigger);
}

//////////////////////////////////////////////////////////////////////////

HudExchangeInventorySystem::HudExchangeInventorySystem()
{
}

HudExchangeInventorySystem::~HudExchangeInventorySystem()
{
}

void HudExchangeInventorySystem::init()
{
	menuA = new HudExchangeInventoryMenu();
	menuB = new HudExchangeInventoryMenu();

	menuA->setPosition(75, 550);
	menuB->setPosition(425, 550);

	menuA->hide();
	menuB->hide();
}

void HudExchangeInventorySystem::close()
{
	menuA->hide();
	menuB->hide();

	KeyController::getInstance()->switchCtrlToPlayer();
}

void HudExchangeInventorySystem::AgiveB()
{
	int curIndex = menuA->getCurIndex();

	std::string inventoryName = characterA->queryInventoryNameByIndex(curIndex);
	characterA->removeInventory(inventoryName);

	characterB->addInventory(inventoryName);

	menuA->update();
	menuB->update();
	HudCursor::getInstance()->setCurMenu(menuA);

}

void HudExchangeInventorySystem::exchangeInventory(Character* A, Character* B)
{
	KeyController::getInstance()->switchCtrlToExchangeInv();

	characterA = A;
	characterB = B;

	menuA->setCharacter(A);
	menuB->setCharacter(B);

	menuA->update();
	menuB->update();

	menuB->show();
	menuA->show();

	HudCursor::getInstance()->setCurMenu(menuA);
	HudCursor::getInstance()->show();
}
