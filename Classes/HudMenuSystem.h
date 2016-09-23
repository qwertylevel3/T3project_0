#pragma once

#include "Singleton.h"
#include"base\CCEventKeyboard.h"
#include "base\ccTypes.h"

class HudMenu;
class HudInventoryMenu;
class HudEquipMenu;

class HudMenuSystem:public Singleton<HudMenuSystem>
{
public:
	HudMenuSystem();
	~HudMenuSystem();
	void init();
	void update();
	void show();
	void hide();
	void handleKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode);
protected:
	void initMainMenu();
	void initInventoryMenu();
	void initActiveMenu();
	void initEquipMenu();
	HudMenu* mainMenu;
	HudInventoryMenu* inventoryMenu;
	HudEquipMenu* equipMenu;
	cocos2d::Vec2 windowSize;
};

