#pragma once

#include "Singleton.h"
#include "base/ccTypes.h"

class MyCamera:public Singleton<MyCamera>
{
public:
	MyCamera();
	~MyCamera();
	void moveCamera(cocos2d::Point position,float time);
	void setCamera(cocos2d::Point position);
protected:
};

