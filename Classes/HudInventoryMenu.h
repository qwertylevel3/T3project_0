#pragma once

#include "Singleton.h"
#include "HudMenu.h"

class HudInventoryMenu:public HudMenu
{
public:
	HudInventoryMenu(cocos2d::Rect rect);
	~HudInventoryMenu();
	void update();
protected:
};

