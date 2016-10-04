#include "HudTrigUnequipRight.h"
#include "Player.h"
#include "HudEquipMenu.h"
#include "HudMenuItem.h"



HudTrigUnequipRight::HudTrigUnequipRight()
{
}


HudTrigUnequipRight::~HudTrigUnequipRight()
{
}

void HudTrigUnequipRight::run()
{
	Character* characterPtr = Player::getInstance()->getcharacterPtr();
	characterPtr->unequipRightHand();

	HudEquipMenu::getInstance()->update();
	menuItem->getParentMenu()->closeMenu();
}
