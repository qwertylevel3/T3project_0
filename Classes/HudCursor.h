#pragma once

#include"Singleton.h"
#include"base\CCEventKeyboard.h"
#include"2d\CCSprite.h"
class HudMenuItem;

class HudCursor:public Singleton<HudCursor>
{
public:
	HudCursor();
	~HudCursor();

	void handleKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode);
	void moveUp();
	void moveDown();
protected:
	HudMenuItem* curItem;
	cocos2d::Sprite* sprite;
};

