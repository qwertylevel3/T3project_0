#pragma once

#include "2d/CCLayer.h"
#include "Singleton.h"

class MenuLayer:public cocos2d::Layer,public Singleton<MenuLayer>
{
public:
	MenuLayer();
	~MenuLayer();
	bool init();
};

