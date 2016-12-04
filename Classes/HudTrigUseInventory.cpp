#include "HudTrigUseInventory.h"
#include "HudInventoryMenu.h"
#include "InventoryHandler.h"
#include "Character.h"
#include "Supply.h"
#include "Player.h"
#include "HudMenuItem.h"



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

	InventoryHandler* inventoryHandler = characterPtr->getInventoryHandler();
	Inventory* inventory = inventoryHandler->getInventory(curIndex);

//	characterPtr->equipLeftHand(inventory);
	inventory->use(characterPtr);
	delete inventory;

	menuItem->getParentMenu()->closeMenu();
}
