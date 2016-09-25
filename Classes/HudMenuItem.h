#pragma once

#include"2d\CCLabel.h"
#include<vector>
#include"2d\CCSprite.h"
#include"platform\CCPlatformMacros.h"
class HudMenu;
class HudTrigger;


class HudMenuItem
{
public:
	HudMenuItem(const std::string& name);
	virtual ~HudMenuItem();
	void active();
	void setTrigger(HudTrigger* t);

	void show();
	void hide();
	void setPosition(cocos2d::Point position);
	cocos2d::Point getPosition();
	int getHeight();
	int getWidth();
	void setWidth(int w);
	void setHeight(int h);
	void setAliginment(cocos2d::TextHAlignment alignment);
	cocos2d::Label* getLabel();
protected:
	CC_SYNTHESIZE(cocos2d::Point, marginal, Marginal);
	CC_SYNTHESIZE(HudMenu*, parentMenu, ParentMenu);
	cocos2d::Label* label;
	HudTrigger* trigger;
};

