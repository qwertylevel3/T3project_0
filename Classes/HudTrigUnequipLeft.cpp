#include "HudTrigUnequipLeft.h"
#include "Player.h"
#include "HudEquipMenu.h"



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
}
