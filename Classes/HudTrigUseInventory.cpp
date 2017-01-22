#include "HudTrigUseInventory.h"
#include "KeyController.h"
#include "HudInventoryMenu.h"
#include "InventoryHandler.h"
#include "Character.h"
#include "Supply.h"
#include "InventoryFactory.h"
#include "Player.h"
#include "HudMenuItem.h"
#include "HudMessageBox.h"



HudTrigUseInventory::HudTrigUseInventory()
{
}


HudTrigUseInventory::~HudTrigUseInventory()
{
}

void HudTrigUseInventory::run()
{
	int curIndex = HudInventoryMenu::getInstance()->getCurIndex();
	Character* characterPtr = Player::getInstance()->getcharacterPtr();

	std::string InventoryName = characterPtr->queryInventoryNameByIndex(curIndex);
	Inventory* inventory = InventoryFactory::getInstance()->getInventory(InventoryName);

	Supply* supply = static_cast<Supply*>(inventory);
	if (!checkRequire(supply))
	{
		delete supply;
		return;
	}

	characterPtr->removeInventory(InventoryName);

	supply->use(characterPtr);
	delete supply;

	KeyController::getInstance()->switchCtrlToPlayer();

	menuItem->getParentMenu()->closeMenu();
}

bool HudTrigUseInventory::checkRequire(Supply* supply)
{
	Character* characterPtr = Player::getInstance()->getcharacterPtr();

	int strReq = supply->getStrRequire();
	if (characterPtr->getStrength()<strReq)
	{
		HudMessageBox::getInstance()->addMessage(L"力量需求不够");
		return false;
	}

	int agiReq = supply->getAgiRequire();
	if (characterPtr->getAgility()<agiReq)
	{
		HudMessageBox::getInstance()->addMessage(L"敏捷需求不够");
		return false;
	}
	int intReq = supply->getIntRequire();
	if (characterPtr->getIntellect()<intReq)
	{
		HudMessageBox::getInstance()->addMessage(L"智力需求不够");
		return false;
	}
	return true;
}
