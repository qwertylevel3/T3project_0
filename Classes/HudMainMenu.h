#pragma once

#include "HudMenu.h"
#include "Singleton.h"

class HudMainMenu:public HudMenu,public Singleton<HudMainMenu>
{
public:
	HudMainMenu();
	~HudMainMenu();
	void init();
};

