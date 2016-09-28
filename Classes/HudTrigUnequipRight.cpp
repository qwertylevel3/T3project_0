#include "HudTrigUnequipRight.h"
#include "Player.h"
#include "HudEquipMenu.h"



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
}
