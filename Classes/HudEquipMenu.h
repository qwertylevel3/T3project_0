#pragma once

#include "HudMenu.h"
#include "Singleton.h"

class HudEquipMenu:public HudMenu,public Singleton<HudEquipMenu>
{
public:
	HudEquipMenu();
	~HudEquipMenu();
	void init();
	void addItem(HudMenuItem* item);
protected:
	void update();
};

