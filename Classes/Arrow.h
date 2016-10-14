#pragma once

#include "Inventory.h"

class Arrow:public Inventory
{
public:
	Arrow();
	~Arrow();
	Arrow* clone();
protected:
	CC_SYNTHESIZE(int, damage, Damage);
};

