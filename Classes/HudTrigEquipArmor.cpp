#include "HudTrigEquipArmor.h"
#include "KeyController.h"
#include "HudMenuItem.h"
#include "Player.h"
#include "InventoryFactory.h"
#include "Inventory.h"
#include "Character.h"
#include "HudInventoryMenu.h"



HudTrigEquipArmor::HudTrigEquipArmor()
{
}


HudTrigEquipArmor::~HudTrigEquipArmor()
{
}

void HudTrigEquipArmor::run()
{
	int curIndex = HudInventoryMenu::getInstance()->getCurIndex();
	Character* characterPtr = Player::getInstance()->getcharacterPtr();

	std::string inventoryName = characterPtr->queryInventoryNameByIndex(curIndex);
	characterPtr->removeInventory(inventoryName);
	Inventory* inventory = InventoryFactory::getInstance()->getInventory(inventoryName);

	characterPtr->equipArmor(inventory);
	KeyController::getInstance()->switchCtrlToPlayer();

	menuItem->getParentMenu()->closeMenu();
}
