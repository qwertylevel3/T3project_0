#pragma once

#include "InventoryInHand.h"

class Shield :
	public InventoryInHand
{
public:
	Shield();
	virtual ~Shield();
	Shield* clone();
	void copyData(Shield* inventory);
protected:
	CC_SYNTHESIZE(int, shieldCount, ShieldCount);
};

