#pragma once

#include "HudMenu.h"
#include "Singleton.h"

class HudBuffMenu:public HudMenu,public Singleton<HudBuffMenu>
{
public:
	HudBuffMenu();
	~HudBuffMenu();
	void update();
	void addItem(HudMenuItem* item);
};

