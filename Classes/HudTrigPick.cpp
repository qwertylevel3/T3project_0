#include "HudTrigPick.h"
#include "Dungeon.h"
#include "HudMenu.h"
#include "HudMenuItem.h"
#include "HudGroundMenu.h"
#include "InventoryHandler.h"
#include "StoreyInventoryHandler.h"
#include "Player.h"

HudTrigPick::HudTrigPick()
{
}

HudTrigPick::~HudTrigPick()
{
}

void HudTrigPick::run()
{
	int curIndex = HudGroundMenu::getInstance()->getCurIndex();

	Character* characterPtr = Player::getInstance()->getcharacterPtr();

	Field::Storey* storey = Field::Dungeon::getInstance()->getStorey();
	StoreyInventoryHandler* storeyInventoryHandler = storey->getInventoryHandler();
	Inventory* ivnentory = storeyInventoryHandler->getInventory(curIndex,
		characterPtr->getMapCoord().x,
		characterPtr->getMapCoord().y);
	storeyInventoryHandler->removeInventory(curIndex,
		characterPtr->getMapCoord().x,
		characterPtr->getMapCoord().y);

	characterPtr->getInventoryHandler()->addInventory(ivnentory);

	menuItem->getParentMenu()->closeMenu();
}