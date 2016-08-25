#pragma once

#include"Singleton.h"
#include"base\CCEventKeyboard.h"
#include"2d\CCSprite.h"
class HudMenu;

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
	void setCurMenu(HudMenu* menu);

	void handleLeft();
	void handleRight();
	void handleUp();
	void handleDown();
protected:
	HudMenu* curMenu;
	cocos2d::Sprite* sprite;
};

