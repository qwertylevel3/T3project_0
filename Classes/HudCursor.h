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

	void setPosition(cocos2d::Point position);
	void handleKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode);
	void moveUp(int offset);
	void moveDown(int offset);
	void show();
	void hide();
	cocos2d::Sprite* getSprite();
	void setCurItem(HudMenuItem* item);

	void handleLeft();
	void handleRight();
	void handleUp();
	void handleDown();
protected:
	HudMenuItem* curItem;
	cocos2d::Sprite* sprite;
};

