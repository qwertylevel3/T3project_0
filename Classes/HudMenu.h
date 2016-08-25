#pragma once

#include"Singleton.h"
class HudMenuItem;
#include <vector>
#include"2d\CCSprite.h"


class HudMenu
{
public:
	HudMenu(cocos2d::Rect rect);
	~HudMenu();
	virtual void update();
	virtual void handleUp();
	virtual void handleDown();
	virtual void handleLeft();
	virtual void handleRight();
	void show();
	void hide();
	void setPosition(int x,int y);
	void setCursorPosition(int index);
	void initCursor();
	void addItem(HudMenuItem* item);
	int getWidth();
	int getHeight();
	cocos2d::Sprite* getSprite();
	void chooseItem(int index);
	void activeChildMenu(int index);
	void setParent(HudMenu* p);
protected:
	void clear();
	HudMenu* parent;
	//ÄÚ±ß¿ò¾à
	cocos2d::Vec2 marginal;
	cocos2d::Sprite* sprite;
	std::vector<HudMenuItem*> itemList;
	int itemIndex;
};

