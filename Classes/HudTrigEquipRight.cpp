#include "HudTrigEquipRight.h"
#include "HudInventoryMenu.h"
#include "Player.h"
#include "InventoryHandler.h"
#include "HudMenuItem.h"
#include "InventoryFactory.h"



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

	std::string inventoryName = characterPtr->queryInventoryNameByIndex(curIndex);
	characterPtr->removeInventory(inventoryName);

	Inventory* inventory = InventoryFactory::getInstance()->getInventory(inventoryName);

	characterPtr->equipRightHand(inventory);

	menuItem->getParentMenu()->closeMenu();
}
