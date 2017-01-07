#include "HudTrigUnequipArmor.h"
#include "HudMenu.h"
#include "Player.h"
#include "HudMenuItem.h"
#include "Character.h"



HudTrigUnequipArmor::HudTrigUnequipArmor()
{
}


HudTrigUnequipArmor::~HudTrigUnequipArmor()
{
}

void HudTrigUnequipArmor::run()
{
	Character* characterPtr = Player::getInstance()->getcharacterPtr();
	characterPtr->unequipArmor();

	menuItem->getParentMenu()->closeMenu();
}
