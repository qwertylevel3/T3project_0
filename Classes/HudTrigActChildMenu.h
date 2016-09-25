#pragma once

#include "HudTrigger.h"
#include "base\ccMacros.h"

class HudMenu;

class HudTrigActChildMenu:public HudTrigger
{
public:
	HudTrigActChildMenu();
	HudTrigActChildMenu(HudMenu* relateMenu);
	~HudTrigActChildMenu();
	void run();
protected:
	CC_SYNTHESIZE(HudMenu*, relateMenu, RelateMenu);
};

