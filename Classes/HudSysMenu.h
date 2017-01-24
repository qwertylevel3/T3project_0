#pragma once

#include "HudMenu.h"
#include "Singleton.h"

class HudSysMenu:public HudMenu,public Singleton<HudSysMenu>
{
public:
	HudSysMenu();
	~HudSysMenu();
	void addItem(HudMenuItem* item);
protected:
};

