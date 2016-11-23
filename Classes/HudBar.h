#pragma once

#include "Singleton.h"

namespace cocos2d
{
	class Sprite;
}

class HudBar:public Singleton<HudBar>
{
public:
	HudBar();
	~HudBar();
	void init();
	void update();
	void show();
	void hide();
protected:
	cocos2d::Sprite* hpBarBk;
	cocos2d::Sprite* mpBarBk;
	cocos2d::Sprite* hpBar;
	cocos2d::Sprite* mpBar;
};

