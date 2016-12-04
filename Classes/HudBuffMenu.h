#pragma once

#include "HudMenu.h"
#include "Singleton.h"

class HudBuffMenu:public HudMenu,public Singleton<HudBuffMenu>
{
public:
	HudBuffMenu();
	~HudBuffMenu();
	void show();
	void hide();
	void update();
	void chooseItem(int index);
	void addItem(HudMenuItem* item);
};

