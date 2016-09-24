#pragma once

#include "HudMenuItemTrigger.h"
#include "base\ccMacros.h"

class HudMenu;

class HudTrigActChildMenu:public HudMenuItemTrigger
{
public:
	HudTrigActChildMenu();
	HudTrigActChildMenu(HudMenu* relateMenu);
	~HudTrigActChildMenu();
	void run();
protected:
	CC_SYNTHESIZE(HudMenu*, relateMenu, RelateMenu);
};

