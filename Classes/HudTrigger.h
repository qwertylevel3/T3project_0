#pragma once

class HudMenuItem;

class HudTrigger
{
public:
	HudTrigger();
	virtual ~HudTrigger();
	virtual void run() = 0;
	void setMenuItem(HudMenuItem* item);
protected:
	HudMenuItem* menuItem;
};

