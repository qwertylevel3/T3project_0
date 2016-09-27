#include "HudTrigEquipLeft.h"
#include "Player.h"
#include "HudInventoryMenu.h"
#include "InventoryHandler.h"
#include "Inventory.h"


HudTrigEquipLeft::HudTrigEquipLeft()
{
}

HudTrigEquipLeft::~HudTrigEquipLeft()
{
}

void HudTrigEquipLeft::run()
{
	int curIndex = HudInventoryMenu::getInstance()->getCurIndex();
	Character* characterPtr = Player::getInstance()->getcharacterPtr();

	InventoryHandler* inventoryHandler = characterPtr->getInventoryHandler();
	Inventory* inventory = inventoryHandler->getInventory(curIndex);

	characterPtr->equipLeftHand(inventory);

	HudInventoryMenu::getInstance()->update();
}
