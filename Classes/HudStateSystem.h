#pragma once

#include "Singleton.h"
#include "2d/CCLabel.h"

class HudStateSystem:public Singleton<HudStateSystem>
{
public:
	HudStateSystem();
	~HudStateSystem();
	void init();
	void update();
protected:
	void setPosition();

	cocos2d::Label* playerNameLabel;
	cocos2d::Label* hpLabel;
	cocos2d::Label* mpLabel;
	cocos2d::Label* strLabel;
	cocos2d::Label* agiLabel;
	cocos2d::Label* intLabel;

	cocos2d::Label* leftAtkLabel;
	cocos2d::Label* rightAtkLabel;
	cocos2d::Label* leftCriAtkLabel;
	cocos2d::Label* rightCriAtkLabel;
	cocos2d::Label* leftCriProLabel;
	cocos2d::Label* rightCriProLabel;
	cocos2d::Label* leftAccuracyCountLabel;
	cocos2d::Label* rightAccuracyCountLabel;

	cocos2d::Label* evadeCountLabel;
	cocos2d::Label* blockCountLable;
	cocos2d::Label* blockProCountLabel;
	cocos2d::Label* comboProCountLable;
};

