#pragma once

#include "Singleton.h"
#include "2d/CCLabel.h"
#include "2d/CCSprite.h"
#include "ui/UILayout.h"

class HudPlayerStateMenu:public Singleton<HudPlayerStateMenu>
{
public:
	HudPlayerStateMenu();
	~HudPlayerStateMenu();
	void init();
	void update();
	void show();
	void hide();
protected:
	void setPosition();
//	cocos2d::Sprite* bk;
	cocos2d::ui::Layout* bk;

	cocos2d::Label* playerNameLabel;
	cocos2d::Label* hpLabel;
	cocos2d::Label* mpLabel;
	cocos2d::Label* chantLabel;

	cocos2d::Label* strLabel;
	cocos2d::Label* agiLabel;
	cocos2d::Label* intLabel;
//	cocos2d::Label* luckLabel;

	cocos2d::Label* weightLabel;
//	cocos2d::Label* goldLabel;
};

