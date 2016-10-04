#include "HudTrigUnequipLeft.h"
#include "Player.h"
#include "HudEquipMenu.h"
#include "HudMenuItem.h"



HudTrigUnequipLeft::HudTrigUnequipLeft()
{
}


HudTrigUnequipLeft::~HudTrigUnequipLeft()
{
}

void HudTrigUnequipLeft::run()
{
	Character* characterPtr = Player::getInstance()->getcharacterPtr();
	characterPtr->unequipLeftHand();

	menuItem->getParentMenu()->closeMenu();
}
