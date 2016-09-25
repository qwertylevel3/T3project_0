#pragma once

#include "Singleton.h"
#include "HudMenu.h"

class HudInventoryMenu:public HudMenu,public Singleton<HudInventoryMenu>
{
public:
	HudInventoryMenu();
	~HudInventoryMenu();
	void update();
	void init();
	void addItem(HudMenuItem* item);
protected:
	void setItemTrigger(const std::string& inventoryName,HudMenuItem* item);
	void initEquipableInventoryMenu(HudMenuItem* item);
};

