#pragma once

#include"cocos2d.h"
#include"Singleton.h"

class HudLayer:public cocos2d::Layer,public Singleton<HudLayer>
{
public:
	HudLayer();
	~HudLayer();
	void update();
};

