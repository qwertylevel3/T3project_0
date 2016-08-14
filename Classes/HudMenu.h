#pragma once

#include"Singleton.h"
class HudMenuItem;

class HudMenu:public Singleton<HudMenu>
{
public:
	HudMenu();
	~HudMenu();
	void init();
	void show();
	void hide();
protected:
	HudMenuItem* menu;
};

