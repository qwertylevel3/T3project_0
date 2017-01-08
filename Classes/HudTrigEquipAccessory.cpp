#include "HudTrigEquipAccessory.h"
#include "Player.h"
#include "InventoryFactory.h"
#include "Character.h"
#include "Inventory.h"
#include "HudInventoryMenu.h"
#include "HudMenu.h"
#include "HudMenuItem.h"



HudTrigEquipAccessory::HudTrigEquipAccessory()
{
}


HudTrigEquipAccessory::~HudTrigEquipAccessory()
{
}

void HudTrigEquipAccessory::run()
{
	int curIndex = HudInventoryMenu::getInstance()->getCurIndex();
	Character* characterPtr = Player::getInstance()->getcharacterPtr();

	std::string inventoryName = characterPtr->queryInventoryNameByIndex(curIndex);
	characterPtr->removeInventory(inventoryName);
	Inventory* inventory = InventoryFactory::getInstance()->getInventory(inventoryName);

	characterPtr->equipAccessory(inventory);

	menuItem->getParentMenu()->closeMenu();
}
