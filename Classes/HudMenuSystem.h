#pragma once

#include "Singleton.h"
#include"base\CCEventKeyboard.h"
#include "base\ccTypes.h"
#include "2d\CCLabel.h"

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
	bool isOpen();
protected:
	cocos2d::Vec2 windowSize;

	//²Ëµ¥ÊÇ·ñ¿ªÆô
	bool open;

};

