#pragma once

#include"2d\CCLabel.h"
#include<vector>
#include"2d\CCSprite.h"
#include"platform\CCPlatformMacros.h"
class HudMenu;

class HudMenuItem
{
public:
	HudMenuItem(const std::wstring& name);
	~HudMenuItem();

	void show();
	void hide();
	void setPosition(cocos2d::Point position);
	void setMenu(HudMenu* menu);
	cocos2d::Point getPosition();
	std::string getUTF8name();
	int getHeight();
	int getWidth();
	cocos2d::Label* getLabel();
protected:
	CC_SYNTHESIZE(std::wstring, name, Name);
	CC_SYNTHESIZE(cocos2d::Point, marginal, marginal);
	HudMenu* relateMenu;
	cocos2d::Label* label;
};

