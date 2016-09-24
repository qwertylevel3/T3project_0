#pragma once

#include "Singleton.h"
#include "HudMenu.h"

class HudInventoryMenu:public HudMenu
{
public:
	HudInventoryMenu(cocos2d::Rect rect);
	~HudInventoryMenu();
	void update();
	void addItem(HudMenuItem* item);
protected:
	void setItemTrigger(const std::string& inventoryName,HudMenuItem* item);
	void initEquipableInventory(HudMenuItem* item);
};

