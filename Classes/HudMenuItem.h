#pragma once

#include"2d\CCLabel.h"
#include<vector>
#include"2d\CCSprite.h"
#include"platform\CCPlatformMacros.h"

class HudMenuItem
{
public:
	HudMenuItem(cocos2d::Rect rect);
	~HudMenuItem();

	virtual void handleUp();
	virtual void handleDown();
	virtual void handleLeft();
	virtual void handleRight();
	void show();
	void hide();
	void addChildItem(HudMenuItem* item);
	cocos2d::Sprite* getSprite();
	void setPosition(cocos2d::Point position);
protected:
	CC_SYNTHESIZE(std::string, name, Name);
	cocos2d::Sprite* sprite;
	std::vector<HudMenuItem* > childList;
	std::vector<cocos2d::Label* > labelList;
	HudMenuItem* parent;
	int curIndex;
};

