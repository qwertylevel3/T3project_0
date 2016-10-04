#include "HudTrigEquipRight.h"
#include "HudInventoryMenu.h"
#include "Player.h"
#include "InventoryHandler.h"
#include "HudMenuItem.h"



HudTrigEquipRight::HudTrigEquipRight()
{
}


HudTrigEquipRight::~HudTrigEquipRight()
{
}

void HudTrigEquipRight::run()
{
	int curIndex = HudInventoryMenu::getInstance()->getCurIndex();
	Character* characterPtr = Player::getInstance()->getcharacterPtr();

	InventoryHandler* inventoryHandler = characterPtr->getInventoryHandler();
	Inventory* inventory = inventoryHandler->getInventory(curIndex);

	characterPtr->equipRightHand(inventory);

	menuItem->getParentMenu()->closeMenu();
}
