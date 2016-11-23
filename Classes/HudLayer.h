#pragma once

#include"cocos2d.h"
#include"Singleton.h"
#include<vector>

class HudSender;

class HudLayer:public cocos2d::Layer,public Singleton<HudLayer>
{
public:
	HudLayer();
	~HudLayer();
	virtual bool init();
	void update();
	void show();
	void hide();
protected:
	std::vector<HudSender* > senderList;
};

