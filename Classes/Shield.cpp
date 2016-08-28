#include "Shield.h"



Shield::Shield()
{
}


Shield::~Shield()
{
}

Shield* Shield::clone()
{
	Shield* shield = new Shield();
	copyData(shield);

	return shield;
}

void Shield::copyData(Shield* inventory)
{
	InventoryInHand::copyData(inventory);
	inventory->setShieldCount(shieldCount);
	inventory->setInventoryType(Inventory::Shield);
}
