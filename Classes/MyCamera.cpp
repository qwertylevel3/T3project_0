#include "MyCamera.h"
#include "MainLayer.h"
#include "MaskLayer.h"
#include "Dungeon.h"
#include "base/CCDirector.h"



MyCamera::MyCamera()
{
}


MyCamera::~MyCamera()
{
}

void MyCamera::moveCamera(cocos2d::Point position, float time)
{
	
}

void MyCamera::setCamera(cocos2d::Point position)
{
	auto winSize = cocos2d::Director::getInstance()->getWinSize();

	auto centerOfView = cocos2d::Point(winSize.width / 2, winSize.height / 2);
	auto viewPoint = centerOfView - position;

	MainLayer::getInstance()->setPosition(viewPoint);
	MaskLayer::getInstance()->setPosition(viewPoint);
}
