#pragma once

#include "Singleton.h"
#include"base\CCEventKeyboard.h"

class HudMenu;
class HudInventoryMenu;

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
	void initMainMenu();
	void initInventoryMenu();
	HudMenu* mainMenu;
	HudInventoryMenu* inventoryMenu;
};

