#pragma once

#include "2d/CCLayer.h"
#include "Singleton.h"

namespace cocos2d
{
	class Sprite;
}

class SplashLayer:public cocos2d::Layer,public Singleton<SplashLayer>
{
public:
	static void startMission(SplashLayer* layer);
	SplashLayer();
	~SplashLayer();
	bool init();
	void showLogo(float dt);
	void fadeOutBlack(float dt);
	void fadeInBlack(float dt);
protected:
	cocos2d::Sprite* logo;
	cocos2d::Sprite* black;
};

