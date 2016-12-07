#include "HudTrigUseInventory.h"
#include "HudInventoryMenu.h"
#include "InventoryHandler.h"
#include "Character.h"
#include "Supply.h"
#include "InventoryFactory.h"
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


	std::string InventoryName = characterPtr->queryInventoryNameByIndex(curIndex);
	characterPtr->removeInventory(InventoryName);

	Inventory* inventory = InventoryFactory::getInstance()->getInventory(InventoryName);

//	characterPtr->equipLeftHand(inventory);
	inventory->use(characterPtr);
	delete inventory;

	menuItem->getParentMenu()->closeMenu();
}
