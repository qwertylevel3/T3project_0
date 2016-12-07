#include "HudTrigDrop.h"
#include "Player.h"
#include "HudInventoryMenu.h"
#include "InventoryHandler.h"
#include "Dungeon.h"
#include "InventoryFactory.h"
#include "StoreyInventoryHandler.h"
#include "HudMenuItem.h"



HudTrigDrop::HudTrigDrop()
{
}


HudTrigDrop::~HudTrigDrop()
{
}

void HudTrigDrop::run()
{
	int curIndex = HudInventoryMenu::getInstance()->getCurIndex();
	Character* characterPtr = Player::getInstance()->getcharacterPtr();


	std::string inventoryName = characterPtr->queryInventoryNameByIndex(curIndex);
	characterPtr->removeInventory(inventoryName);

	Inventory* inventory = InventoryFactory::getInstance()->getInventory(inventoryName);

	Field::Storey* storey=Field::Dungeon::getInstance()->getStorey();
	storey->getInventoryHandler()->addInventory(inventory,characterPtr->getMapCoord().x,characterPtr->getMapCoord().y);

	menuItem->getParentMenu()->closeMenu();
}
