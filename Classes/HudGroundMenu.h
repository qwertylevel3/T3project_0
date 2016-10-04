#pragma once

#include "HudMenu.h"
#include "Singleton.h"

class HudGroundMenu:public HudMenu,public Singleton<HudGroundMenu>
{
public:
	HudGroundMenu();
	~HudGroundMenu();
	void addItem(HudMenuItem* item);
	void update();
};

