#include "HudTrigUnequipAccessory.h"
#include "HudMenuItem.h"
#include "HudMenu.h"
#include "Character.h"
#include "Player.h"



HudTrigUnequipAccessory::HudTrigUnequipAccessory()
{
}


HudTrigUnequipAccessory::~HudTrigUnequipAccessory()
{
}

void HudTrigUnequipAccessory::run()
{
	Character* characterPtr = Player::getInstance()->getcharacterPtr();
	characterPtr->unequipAccessory();

	menuItem->getParentMenu()->closeMenu();
}
