#include "HudTrigEquipLeft.h"
#include "KeyController.h"
#include "Player.h"
#include "HudInventoryMenu.h"
#include "InventoryHandler.h"
#include "InventoryFactory.h"
#include "Inventory.h"
#include "HudMenuItem.h"


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

	std::string inventoryName = characterPtr->queryInventoryNameByIndex(curIndex);
	characterPtr->removeInventory(inventoryName);
	Inventory* inventory = InventoryFactory::getInstance()->getInventory(inventoryName);

	characterPtr->equipLeftHand(inventory);

	KeyController::getInstance()->switchCtrlToPlayer();

	menuItem->getParentMenu()->closeMenu();

}
