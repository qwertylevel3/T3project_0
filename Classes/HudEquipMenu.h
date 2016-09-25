#pragma once

#include "HudMenu.h"
#include "Singleton.h"

class HudEquipMenu:public HudMenu,public Singleton<HudEquipMenu>
{
public:
	HudEquipMenu();
	~HudEquipMenu();
	void init();
protected:
	void update();
};

