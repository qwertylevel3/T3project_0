#pragma once

#include "HudMenu.h"

class HudEquipMenu:public HudMenu
{
public:
	HudEquipMenu(cocos2d::Rect rect);
	~HudEquipMenu();
protected:
	void update();
};

