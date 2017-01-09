#include "HudTrigGiveInv.h"
#include "HudExchangeInventorySystem.h"



HudTrigGiveInv::HudTrigGiveInv()
{
}


HudTrigGiveInv::~HudTrigGiveInv()
{
}

void HudTrigGiveInv::run()
{
		HudExchangeInventorySystem::getInstance()->AgiveB();
}
