#pragma once

#include"cocos2d.h"
#include"Singleton.h"
#include<vector>
#include"HudSender.h"

class HudLayer:public cocos2d::Layer,public Singleton<HudLayer>
{
public:
	HudLayer();
	~HudLayer();
	void update();
	void addSender(HudSender* sender);
protected:
	std::vector<HudSender* > senderList;
};

