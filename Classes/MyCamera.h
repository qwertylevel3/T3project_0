#pragma once

#include "Singleton.h"
#include "base/ccTypes.h"

class MyCamera:public Singleton<MyCamera>
{
public:
	MyCamera();
	~MyCamera();
	void moveCameraTo(cocos2d::Point position,float time);
	void moveCameraBy(cocos2d::Vec2 direction,float time);
	void setCamera(cocos2d::Point position);
protected:
	cocos2d::Point calculateViewCenter(cocos2d::Point position);
};

