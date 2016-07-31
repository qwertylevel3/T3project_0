#include "HudLayer.h"

USING_NS_CC;

HudLayer::HudLayer()
{
}


HudLayer::~HudLayer()
{
}

void HudLayer::update()
{
	for (int i = 0; i < senderList.size(); i++)
	{
		senderList[i]->updateSender();
	}
}

void HudLayer::addSender(HudSender* sender)
{
	senderList.push_back(sender);

	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	auto label = sender->getSenderLable();
	label->setPosition(Vec2(origin.x + 100,
		origin.y + 100 - label->getContentSize().height));

	this->addChild(label, 2);
}
