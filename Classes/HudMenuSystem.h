#pragma once

#include "Singleton.h"
#include"base\CCEventKeyboard.h"

class HudMenu;

class HudMenuSystem:public Singleton<HudMenuSystem>
{
public:
	HudMenuSystem();
	~HudMenuSystem();
	void init();
	void show();
	void hide();
	void handleKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode);
protected:
	HudMenu* menu;
};

