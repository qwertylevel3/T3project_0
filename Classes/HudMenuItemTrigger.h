#pragma once

class HudMenuItem;

class HudMenuItemTrigger
{
public:
	HudMenuItemTrigger();
	~HudMenuItemTrigger();
	virtual void run() = 0;
	void setMenuItem(HudMenuItem* item);
protected:
	HudMenuItem* menuItem;
};

