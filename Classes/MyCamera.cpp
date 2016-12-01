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

void MyCamera::moveCameraTo(cocos2d::Point position, float time)
{
	auto viewPoint = calculateViewCenter(position);

	MainLayer::getInstance()->runAction(
		cocos2d::MoveTo::create(time, viewPoint)
	);
	MaskLayer::getInstance()->runAction(
		cocos2d::MoveTo::create(time, viewPoint)
	);
}

void MyCamera::moveCameraBy(cocos2d::Vec2 direction, float time)
{
	MainLayer::getInstance()->runAction(
		cocos2d::MoveBy::create(time, -direction)
	);
	MaskLayer::getInstance()->runAction(
		cocos2d::MoveBy::create(time, -direction)
	);
}

void MyCamera::setCamera(cocos2d::Point position)
{
	auto viewPoint = calculateViewCenter(position);

	MainLayer::getInstance()->setPosition(viewPoint);
	MaskLayer::getInstance()->setPosition(viewPoint);
}

cocos2d::Point MyCamera::calculateViewCenter(cocos2d::Point position)
{
	auto winSize = cocos2d::Director::getInstance()->getWinSize();

	auto centerOfView = cocos2d::Point(winSize.width / 2, winSize.height / 2);
	return centerOfView - position;
}