#pragma once

class HudMenuItem;

class HudTrigger
{
public:
	HudTrigger();
	~HudTrigger();
	virtual void run() = 0;
	void setMenuItem(HudMenuItem* item);
protected:
	HudMenuItem* menuItem;
};

