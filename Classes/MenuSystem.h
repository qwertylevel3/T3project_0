#pragma once

#include "Singleton.h"


class MenuSystem:public Singleton<MenuSystem>
{
public:
	MenuSystem();
	~MenuSystem();
	void init();
	void show();
	void hide();
};

