#pragma once

#include"Singleton.h"
#include"cocos2d.h"

class Debug:public Singleton<Debug>
{
public:
	Debug();
	~Debug();
	void showMessage(std::string message,cocos2d::Point position);
	void init(cocos2d::Layer* layerPtr);
private:
	CC_SYNTHESIZE(cocos2d::Layer*, layer, Layer);
	CC_SYNTHESIZE(bool, debugFlag, DebugFlag);
};
