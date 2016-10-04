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

	HudEquipMenu::getInstance()->update();
	menuItem->getParentMenu()->closeMenu();
}
