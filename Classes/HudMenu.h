#pragma once

#include"Singleton.h"
class HudMenuItem;
#include <vector>
#include"2d\CCSprite.h"


class HudMenu
{
public:
	HudMenu(cocos2d::Rect rect=cocos2d::Rect(0,0,0,0));
	~HudMenu();
	virtual void update();

	//处理键盘按键
	virtual void handleUp();
	virtual void handleDown();
	virtual void handleLeft();
	virtual void handleRight();

	void show();
	void hide();

	void setPosition(int x,int y);
	void setCursorPosition(int index);
	void initCursor();
	virtual void addItem(HudMenuItem* item);
	void setWidth(int w);
	void setHeight(int h);
	int getWidth();
	int getHeight();
	void chooseItem(int index);
	void activeChildMenu(int index);
	void setParent(HudMenu* p);
	void closeMenu();
	void increaseIndex();
	void decreaseIndex();
	cocos2d::Sprite* getSprite();
	void clear();
	int getMarginalWidth();
	int getMarginalHeight();
protected:
	HudMenu* parent;
	//内边框距
	cocos2d::Vec2 marginal;
	cocos2d::Sprite* sprite;
	std::vector<HudMenuItem*> itemList;
	int itemIndex;
};

