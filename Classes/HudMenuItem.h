#pragma once

#include"2d\CCLabel.h"
#include<vector>
#include"2d\CCSprite.h"
#include"platform\CCPlatformMacros.h"
class HudMenu;

class HudMenuItem
{
public:
	HudMenuItem(const std::string& name);
	~HudMenuItem();

	void show();
	void hide();
	void setPosition(cocos2d::Point position);
	void setMenu(HudMenu* menu);
	cocos2d::Point getPosition();
	int getHeight();
	int getWidth();
	void setWidth(int w);
	void setHeight(int h);
	void setAliginment(cocos2d::TextHAlignment alignment);
	cocos2d::Label* getLabel();
protected:
	CC_SYNTHESIZE(cocos2d::Point, marginal, marginal);
	CC_SYNTHESIZE(HudMenu*, relateMenu, RelateMenu);
	cocos2d::Label* label;
};

