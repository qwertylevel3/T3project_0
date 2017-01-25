#pragma once

#include "2d/CCLabel.h"
#include "Singleton.h"

class HudTips:public Singleton<HudTips>
{
public:
	HudTips();
	~HudTips();
	void init();
	void show();
	void hide();
	void update();
protected:
	cocos2d::Label* tip1;
	cocos2d::Label* tip2;

};

