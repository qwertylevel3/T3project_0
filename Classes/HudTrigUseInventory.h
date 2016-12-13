#pragma once

#include "HudTrigger.h"

class Supply;

class HudTrigUseInventory:public HudTrigger
{
public:
	HudTrigUseInventory();
	~HudTrigUseInventory();
	void run();
protected:
	bool checkRequire(Supply* supply);
};

