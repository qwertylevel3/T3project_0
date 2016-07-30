#include "Debug.h"

USING_NS_CC;

Debug::Debug()
{
	layer = nullptr;
	debugFlag = false;
}

void Debug::init(cocos2d::Layer* layerPtr)
{
	layer = layerPtr;
}

Debug::~Debug()
{
}

void Debug::showMessage(std::string message,cocos2d::Point position)
{
	if (layer)
	{
		auto label = cocos2d::Label::createWithTTF(message.c_str(), "fonts/arial.ttf", 24);

		auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
		Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

		label->setPosition(Vec2(origin.x + position.x,
			origin.y + position.y - label->getContentSize().height));

		layer->addChild(label, 2);
	}
}
