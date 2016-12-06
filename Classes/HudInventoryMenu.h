#pragma once

#include "Singleton.h"
#include "HudMenu.h"

class HudInventoryMenu:public HudMenu,public Singleton<HudInventoryMenu>
{
public:
	HudInventoryMenu();
	~HudInventoryMenu();
	void show();
	void hide();
	void update();
	void init();
	void addItem(HudMenuItem* item);
	void chooseItem(int index);
protected:
	void setItemTrigger(const std::string& inventoryName,HudMenuItem* item);
	void initEquipableInventoryMenu(HudMenuItem* item);
	void initUseableInventoryMenu(HudMenuItem* item);
};

